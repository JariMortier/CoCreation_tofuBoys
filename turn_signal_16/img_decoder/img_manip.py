from PIL import Image
import os
import sys

path = "D:\\school\\JAAR3\\CoCreation\\arduino\\turn_signal_16\\img_decoder"
dir_list = os.listdir(path)
pic_list = []

for program in dir_list:
    if ".png" in str(program):
        pic_list.append(program)

print("Beschikbare foto's:")
for n, i in enumerate(pic_list):
    print(f"{n}: {i}")

# Open the fucking image
imgNum = int(input("Nummer van de foto: "))
image = Image.open(f"D:\\school\\JAAR3\\CoCreation\\arduino\\turn_signal_16\\img_decoder\\{pic_list[imgNum]}")

# Get data
pixels = image.load()

# Get RGB values
try:
    width, height = image.size
    if width != 16 or height != 16:
        raise ValueError("Gekozen foto is niet 16 x 16", width, height)
except ValueError as error:
    print(error.args)
    sys.exit("Quit program!")

r_values = []
g_values = []
b_values = []

for y in range(height):
    for x in range(width):
        r, g, b = pixels[x, y]
        r_values.append(str(r))
        g_values.append(str(g))
        b_values.append(str(b))

r_values = r_values[::-1]
g_values = g_values[::-1]
b_values = b_values[::-1]

r_string = "{" + ", ".join(r_values) + "}"
g_string = "{" + ", ".join(g_values) + "}"
b_string = "{" + ", ".join(b_values) + "}"

with open("D:\\school\\JAAR3\\CoCreation\\arduino\\matrix_pics\\matrix_pics.ino", "r") as text:
    lines = text.readlines()

with open("D:\\school\\JAAR3\\CoCreation\\arduino\\matrix_pics\\matrix_pics.ino", "w") as text:
    new_text = ""
    for line in lines:
        if "uint8_t rood[] = " in line:
            new_text += f"uint8_t rood[] = {r_string};\n"
            # print("Found reds")

        elif "uint8_t groen[] = " in line:
            new_text += f"uint8_t groen[] = {g_string};\n"
            # print("Found greens")

        elif "uint8_t blauw[] = " in line:
            new_text += f"uint8_t blauw[] = {b_string};\n"
            # print("Found blues")
        
        else:
            new_text += line
    text.write(new_text)

print(f"Done!\nGekozen foto: {pic_list[imgNum]}")
