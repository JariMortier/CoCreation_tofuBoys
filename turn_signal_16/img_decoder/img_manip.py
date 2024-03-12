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

for y in range(height):
    for x in range(width):
        r, g, b = pixels[x, y]
        r_values.append(str(r))
        g_values.append(str(g))
        b_values.append(str(b))
r_string = "{" + ", ".join(r_values) + "}"
g_string = "{" + ", ".join(g_values) + "}"
b_string = "{" + ", ".join(b_values) + "}"

with open("matrix_pics_backup\matrix_pics_backup.ino", "r") as text:
    lines = text.readlines()

with open("matrix_pics_backup\matrix_pics_backup.ino", "w") as text:
    new_text = ""
    for line in lines:
        #print(line)
        if "uint8_t rood[] = " in line:
            new_text += f"uint8_t rood[] = {r_string};\n"
            print("Found reds")

        elif "uint8_t groen[] = " in line:
            new_text += f"uint8_t groen[] = {g_string};\n"
            print("Found greens")

        elif "uint8_t blauw[] = " in line:
            new_text += f"uint8_t blauw[] = {b_string};\n"
            print("Found blues")
        
        else:
            new_text += line
    text.write(new_text)


#with open("rgb.txt", "w") as text:
#    text.write(f"uint8_t rood[] = {r_string};\nuint8_t groen[] = {g_string};\nuint8_t blauw[] = {b_string};")
print("done!")
