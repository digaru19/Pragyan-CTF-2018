from PIL import Image
import openpyxl
import struct

def transform(p):
    b = p & 0xff
    p = p >> 8
    g = p & 0xff
    p = p >> 8
    r = p
    return r,g,b

def incr_col(col):
    if len(col) == 1:
        if(col == 'Z'):
            next_col = 'AA'
        else:
            next_col = chr(ord(col[0])+1)
        return next_col
    if col[1] == 'Z':
        next_col = chr(ord(col[0])+1) + 'A'
    else:
        next_col = col[0] + chr(ord(col[1])+1)
    return next_col

workbook = openpyxl.load_workbook(filename='transformed.xlsx')
sheet = workbook['Sheet1']

h = 0
w = 0
col = 'A'
t = sheet['A1']

while t is not None:
    t = sheet[col + '1'].value
    h = h + 1
    col = incr_col(col)

t = 1
while t is not None:
    w = w + 1
    t = sheet['A' + str(w)].value
    
print(h,w)

img = Image.new('RGBA', (h-1,w-1))

col = 'A'

for j in range(1,w):
    for i in range(1,h):
        value = sheet[col + str(i)].value
        r,g,b = transform(value)
        img.putpixel((i-1,j-1), (r,g,b,255))
    col = incr_col(col)

img.save('solved.png')

print("\nDone !! \n")
