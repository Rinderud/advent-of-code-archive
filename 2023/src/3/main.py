def is_valid(row) -> bool:
    non_point = row.replace(".", "")
    A = not non_point.isdigit()
    B = len(non_point) != 0
    return A and B


def valid(mtrx, x, y, l) -> bool:
    for i in [-1, 0, 1]:
        j = y + i
        if (j >= 0) and (j < len(mtrx)):
            k1 = x - 1
            k2 = x + l + 1
            if k1 < 0:
                k1 = 0
            if k2 >= len(mtrx[j]):
                k2 = len(mtrx[j]) - 1
            row = mtrx[j][k1:k2]
            if is_valid(row):
                return True
    return False


def part1(mtrx):
    sum = 0
    y = 0
    while y < len(mtrx):
        x = 0
        while x < len(mtrx[y]):
            n = mtrx[y][x]
            if n.isdigit():
                l = 1
                while (x + l < len(mtrx[y])) and (mtrx[y][x + l].isdigit()):
                    l += 1
                num = mtrx[y][x : x + l]
                if valid(mtrx, x, y, l):
                    sum += int(num)
                    print(num, ": 1")
                else:
                    print(num, ": 0")
                x += l

            x += 1
        y += 1
    print(sum)


m = open("2023/src/3/input", "r").read().splitlines()
part1(m)
