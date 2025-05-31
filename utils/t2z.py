#!/usr/bin/python
#########################################################
# t2z.py                                                #
# utility for the zengine game framework                #
#                                                       #
# t2py converts a tiled tilemap to                      #
# a zengine tilemap for use with "src/extras/tilemap"   #
#                                                       #
# USAGE:                                                #
# t2z [sourcename.json] [target.json]                   #
#                                                       #
# LICENSE:                                              #
# just like zEngine itself, t2z is licensed             #
# under the 2-Clause BSD license                        #
# Copyright (C) SpielProfessor 2025                     #
# see LICENSE.txt for more information                  #
#########################################################
import json
import os
import sys
import argparse

def convert_tiled_to_custom(input_file, output_file, ctexture):
    with open(input_file) as f:
        tiled = json.load(f)

    map_width = tiled["width"]
    map_height = tiled["height"]
    tile_size = tiled["tilewidth"]

    # Find tile layer
    layer = next(l for l in tiled["layers"] if l["type"] == "tilelayer")
    tile_data = layer["data"]

    # Tileset info
    tileset = tiled["tilesets"][0]
    firstgid = tileset["firstgid"]
    columns = tileset["columns"]
    tilecount = tileset["tilecount"]
    tileset_image = tileset["image"]
    setname = os.path.splitext(os.path.basename(tileset_image))[0]

    if ctexture != "__ZENGINE_TOOL_T2Z_CTEXNAME_DISABLED":
        setname = ctexture
        
    # Build solid info
    solid_tiles = set()
    for tile in tileset.get("tiles", []):
        for prop in tile.get("properties", []):
            if prop["name"] == "solid" and prop["type"] == "bool" and prop["value"]:
                solid_tiles.add(tile["id"])  # local ID

    tiletypes = {}
    tiles = []
    tiletype_map = {}  # (x, y, solid) -> id
    next_id = 0

    for i, gid in enumerate(tile_data):
        if gid == 0:
            tile_entry = (0, 0, False)
        else:
            local_id = gid - firstgid
            x = local_id % columns
            y = local_id // columns
            solid = local_id in solid_tiles
            tile_entry = (x, y, solid)

        if tile_entry not in tiletype_map:
            tiletype_map[tile_entry] = next_id
            tiletypes[str(next_id)] = [tile_entry[0], tile_entry[1], tile_entry[2]]
            next_id += 1

        tiles.append(tiletype_map[tile_entry])

    # Write output
    with open(output_file, "w") as f:
        f.write("{\n")
        f.write(f'  "width":    {map_width},\n')
        f.write(f'  "height":   {map_height},\n')
        f.write(f'  "tilesize": {tile_size},\n')
        f.write(f'  "setname":  "{setname}",\n')
        f.write(f'  "tiletypes": {{\n')

        for i, (k, v) in enumerate(tiletypes.items()):
            comma = ',' if i < len(tiletypes) - 1 else ''
            f.write(f'    "{k}": [{v[0]}, {v[1]}, {"true" if v[2] else "false"}]{comma}\n')
        f.write("  },\n")

        f.write('  "tiles":\n    [\n')
        for y in range(map_height):
            row = tiles[y * map_width:(y + 1) * map_width]
            row_str = ', '.join(str(n) for n in row)
            comma = ',' if y < map_height - 1 else ''
            f.write(f'      {row_str}{comma}\n')
        f.write("    ]\n")
        f.write("}\n")

    print(f"✅ Converted {input_file} to {output_file}")

                
if __name__ == "__main__":
    # Setup argument parsing
    parser = argparse.ArgumentParser(description="Convert Tiled .json to custom tilemap format")
    parser.add_argument("-i", "--input", required=True, help="Input Tiled .json file")
    parser.add_argument("-o", "--output", required=True, help="Output custom tilemap .json file")
    parser.add_argument("-t", "--texture", default="__ZENGINE_TOOL_T2Z_CTEXNAME_DISABLED", help="Custom texture name to use for the tileset file")
    args = parser.parse_args()
    
    # Now use args.input and args.output like regular variables
    input_file = args.input
    output_file = args.output
    texture = args.texture
    convert_tiled_to_custom(input_file, output_file, texture);

