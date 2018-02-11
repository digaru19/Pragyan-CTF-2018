from PIL import Image
import xlsxwriter
import struct

img = Image.open('trial.png')

h,w = img.size

def transform(p):
    r,g,b,a = p
    value = r << 16
    value += g << 8
    value += b
    return value

workbook = xlsxwriter.Workbook('transformed.xlsx')
sheet = workbook.add_worksheet()

for i in range(h):
    for j in range(w):
        p = img.getpixel((i,j))
        value = transform(p)
        sheet.write(i, j, value)

workbook.close()
