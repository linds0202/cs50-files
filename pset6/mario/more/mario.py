from cs50 import get_int

i = 1
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(0, height):
    
    for j in range(height - 1, -1, -1):
        if j <= i:
            print("#", end="")
        else:
            print(" ", end="")
    print("  ", end="")
    
    for j in range(height):
        if j <= i:
            print("#", end="")
    print("\n")
    