from PIL import Image
from math import *

# Open the fucking image
image = Image.open(r"turn_signal_16\img_decoder\mario.png")

# Get data
pixels = image.load()

# Get RGB values
width, height = image.size
r_values = []
g_values = []
b_values = []

#Fit values to curve to weight
weight = 3

for y in range(height):
    for x in range(width):
        r, g, b = pixels[x, y]
        r_values.append(str(floor(r ** (weight)/255 ** (weight - 1))))
        g_values.append(str(floor(g ** (weight)/255 ** (weight - 1))))
        b_values.append(str(floor(b ** (weight)/255 ** (weight - 1))))
r_string = "{" + ", ".join(r_values) + "}"
g_string = "{" + ", ".join(g_values) + "}"
b_string = "{" + ", ".join(b_values) + "}"

with open("rgb.txt", "w") as text:
    text.write(f"uint8_t rood[] = {r_string};\nuint8_t groen[] = {g_string};\nuint8_t blauw[] = {b_string};")
print("done!")
