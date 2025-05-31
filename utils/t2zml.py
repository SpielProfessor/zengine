#!/usr/bin/python3
import json
import argparse
import os
import sys
from collections import OrderedDict

def load_tilemap(input_path):
    with open(input_path, 'r', encoding='utf-8') as f:
        return json.load(f)

def extract_setname(tileset, user_setname):
    if user_setname:
        return user_setname
    source = tileset.get("image", "")
    return os.path.splitext(os.path.basename(source))[0]

def build_tiletypes(tileset, used_ids):
    firstgid = tileset["firstgid"]
    tilewidth = tileset["tilewidth"]
    tileheight = tileset["tileheight"]
    columns = tileset["columns"]
    tilecount = tileset["tilecount"]

    # Build map from local tile ID to properties
    tiles = {tile["id"]: tile for tile in tileset.get("tiles", [])}

    tiletypes = {}
    for global_id in sorted(used_ids):
        local_id = global_id - firstgid
        if not (0 <= local_id < tilecount):
            continue
        x = local_id % columns
        y = local_id // columns

        props = tiles.get(local_id, {}).get("properties", [])
        collides = False
        for prop in props:
            if prop["name"] == "collides":
                collides = prop["value"]
                break

        tiletypes[str(global_id)] = [x, y, collides]

    return tiletypes

def process_layers(layers):
    result = OrderedDict()
    used_tile_ids = set()
    tile_layers = [layer for layer in layers if layer["type"] == "tilelayer"]
    tile_layers.sort(key=lambda l: layers.index(l))  # Preserve z-order from file

    for index, layer in enumerate(tile_layers):
        width = layer["width"]
        height = layer["height"]
        data = layer["data"]
        used_tile_ids.update(set(data))

        result[str(index)] = {
            "width": width,
            "height": height,
            "tiles": data
        }

    return result, used_tile_ids

def format_layer_tiles(data, width):
    # Pretty-print tile arrays with `width` tiles per line
    lines = []
    for i in range(0, len(data), width):
        row = data[i:i+width]
        lines.append("        " + ", ".join(map(str, row)))
    return lines

def write_output(output_path, tilesize, setname, tiletypes, layers):
    # Manual pretty-printing
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write('{\n')
        f.write(f'  "tilesize": {tilesize},\n')
        f.write(f'  "setname":  "{setname}",\n')
        f.write(f'  "tiletypes": {{\n')

        tiletype_items = list(tiletypes.items())
        for i, (k, v) in enumerate(tiletype_items):
            comma = ',' if i < len(tiletype_items) - 1 else ''
            # Format booleans as JSON-compatible lowercase
            x, y, collides = v
            collides_str = 'true' if collides else 'false'
            f.write(f'    "{k}": [{x}, {y}, {collides_str}]{comma}\n')


        f.write('  },\n')
        f.write('  "layers": {\n')

        layer_items = list(layers.items())
        for i, (z, layer) in enumerate(layer_items):
            comma_layer = ',' if i < len(layer_items) - 1 else ''
            f.write(f'    "{z}": {{\n')
            f.write(f'      "width":    {layer["width"]},\n')
            f.write(f'      "height":   {layer["height"]},\n')
            f.write(f'      "tiles": [\n')

            tile_lines = format_layer_tiles(layer["tiles"], layer["width"])
            for j, line in enumerate(tile_lines):
                comma_tile = ',' if j < len(tile_lines) - 1 else ''
                f.write(line + comma_tile + '\n')

            f.write('      ]\n')
            f.write(f'    }}{comma_layer}\n')

        f.write('  }\n')
        f.write('}\n')

def main():
    parser = argparse.ArgumentParser(description="Convert Tiled .json map to custom format.")
    parser.add_argument("--input", required=True, help="Input .json file exported from Tiled")
    parser.add_argument("--output", required=True, help="Output file path")
    parser.add_argument("--setname", default=None, help="Optional setname override (defaults to image filename)")
    args = parser.parse_args()

    tilemap = load_tilemap(args.input)
    tilesets = tilemap.get("tilesets", [])

    if len(tilesets) != 1:
        print("❌ Error: This converter supports exactly one tileset.", file=sys.stderr)
        sys.exit(1)

    tileset = tilesets[0]
    setname = extract_setname(tileset, args.setname)
    tilesize = tileset["tilewidth"]

    layers, used_tile_ids = process_layers(tilemap["layers"])
    used_tile_ids = {id for id in used_tile_ids if id != 0}  # skip ID 0 (usually empty)

    tiletypes = build_tiletypes(tileset, used_tile_ids)

    write_output(args.output, tilesize, setname, tiletypes, layers)
    print(f"✅ Successfully converted to {args.output}")

if __name__ == "__main__":
    main()

