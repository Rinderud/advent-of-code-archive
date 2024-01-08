def is_valid(row) -> bool:
    non_point = row.replace(".", "")
    A = not non_point.isdigit()
    B = len(non_point) != 0
    return A and B


def valid(mtrx, x, y, l):
    for i in [-1, 0, 1]:
        j = y + i
        if (j >= 0) and (j < len(mtrx)):
            k1 = x - 1
            k2 = x + l + 1
            if k1 < 0:
                k1 = 0
            if k2 >= len(mtrx[j]):
                k2 = len(mtrx[j])
            row = mtrx[j][k1:k2]
            if is_valid(row):
                return True
    return False


def part1(mtrx):
    nbrs = {}
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

                    # For number two
                    for dx in range(-1, l + 1):
                        if (x + dx < len(mtrx[y])) and (x + dx >= 0):
                            for dy in [-1, 0, 1]:
                                if (y + dy < len(mtrx)) and (y + dy >= 0):
                                    symbol = mtrx[y + dy][x + dx]
                                    if symbol != "." and not symbol.isdigit():
                                        key = (x + dx, y + dy)
                                        if key in nbrs:
                                            nbrs[key].append(int(num))
                                        else:
                                            nbrs[key] = [int(num)]
                else:
                    print(num, ": 0")
                x += l

            x += 1
        y += 1
    print("part 1:", sum)
    print(nbrs)
    return nbrs


def part2(mtrx, nbrs):
    sum = 0
    y = 0
    while y < len(mtrx):
        x = 0
        while x < len(mtrx[y]):
            n = mtrx[y][x]
            if n == "*":
                found = nbrs[(x, y)]

                print(found)
                if len(found) == 2:
                    A = found[0]
                    B = found[1]
                    result = A * B
                    sum += result
                    print(A, "*", B, "=", result)
            x += 1
        y += 1
    print("part 2:", sum)


m = open("2023/src/3/input.txt", "r").read().splitlines()
nbrs = part1(m)
print("---")
part2(m, nbrs)
