#!/usr/bin/python3
import os
from PIL import Image
import argparse

def load_tileset_images(folder, tile_size):
    images = []
    for filename in sorted(os.listdir(folder)):
        if filename.lower().endswith((".png", ".jpg")):
            path = os.path.join(folder, filename)
            img = Image.open(path).convert("RGBA")
            if img.width % tile_size != 0 or img.height % tile_size != 0:
                print(f"Skipping {filename}: not aligned to tile size")
                continue
            images.append(img)
    return images

def stitch_images_horizontally(images):
    total_width = sum(img.width for img in images)
    max_height = max(img.height for img in images)
    result = Image.new("RGBA", (total_width, max_height), (0, 0, 0, 0))

    x_offset = 0
    for img in images:
        result.paste(img, (x_offset, 0))
        x_offset += img.width

    return result

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input_folder", help="Folder containing tile-aligned tileset images")
    parser.add_argument("tilesize", type=int, help="Tile size in pixels")
    parser.add_argument("output_file", help="Output atlas file (e.g. 'atlas.png')")
    args = parser.parse_args()

    images = load_tileset_images(args.input_folder, args.tilesize)
    if not images:
        print("No valid images found.")
        return

    atlas = stitch_images_horizontally(images)
    atlas.save(args.output_file)
    print(f"Saved atlas to {args.output_file}")

if __name__ == "__main__":
    main()

