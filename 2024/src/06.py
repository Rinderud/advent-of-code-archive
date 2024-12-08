import time
import logging
import structlog


def interpretInput(input: list[str], log: structlog.BoundLogger):
    output = []
    for row in input:
        output.append([x for x in row])

    return output


def part1(
    interpretation, log: structlog.BoundLogger
) -> tuple[int, set[tuple[int, int]]]:
    h = len(interpretation)
    w = len(interpretation[0])
    log.debug(f"{w} x {h}")

    start: tuple[int, int]
    direction = ""
    for i in range(w):
        for j in range(h):
            if interpretation[j][i] in ["v", "<", ">", "^"]:
                start = (i, j)
                direction = interpretation[j][i]

    log.debug(f"{start=} {direction=}")

    visited: set[tuple[int, int]] = set()
    posX, posY = start
    while (0 <= posX < w) and (0 <= posY < h):
        visited.add((posX, posY))

        match direction:
            case "<":
                try:
                    if interpretation[posY][posX - 1] == "#":
                        direction = "^"
                    else:
                        posX -= 1
                except:
                    posX -= 1

            case ">":
                try:
                    if interpretation[posY][posX + 1] == "#":
                        direction = "v"
                    else:
                        posX += 1
                except:
                    posX += 1

            case "^":
                try:
                    if interpretation[posY - 1][posX] == "#":
                        direction = ">"
                    else:
                        posY -= 1
                except:
                    posY -= 1

            case "v":
                try:
                    if interpretation[posY + 1][posX] == "#":
                        direction = "<"
                    else:
                        posY += 1
                except:
                    posY += 1

        log.debug(f"new: {direction} ({posX} {posY})")

    return (len(visited), visited)


def isInLoop(grid, pos, dir, log) -> bool:
    visited: set[tuple[int, int, str]] = set()
    h = len(grid)
    w = len(grid[0])

    direction = dir
    posX, posY = pos
    while (0 <= posX < w) and (0 <= posY < h):
        new = (posX, posY, direction)
        if new in visited:
            # if posX == pos[0] and posY == pos[1] and direction == dir and len(visited) > 0:
            return True

        visited.add(new)
        # log.debug(f"{new=}")

        match direction:
            case "<":
                try:
                    if interpretation[posY][posX - 1] == "#":
                        direction = "^"
                    else:
                        posX -= 1
                except:
                    posX -= 1

            case ">":
                try:
                    if interpretation[posY][posX + 1] == "#":
                        direction = "v"
                    else:
                        posX += 1
                except:
                    posX += 1

            case "^":
                try:
                    if interpretation[posY - 1][posX] == "#":
                        direction = ">"
                    else:
                        posY -= 1
                except:
                    posY -= 1

            case "v":
                try:
                    if interpretation[posY + 1][posX] == "#":
                        direction = "<"
                    else:
                        posY += 1
                except:
                    posY += 1

    return False


def part2(interpretation, visited, log: structlog.BoundLogger) -> int:
    h = len(interpretation)
    w = len(interpretation[0])
    log.debug(f"{w} x {h}")

    start: tuple[int, int]
    direction = ""
    for i in range(w):
        for j in range(h):
            if interpretation[j][i] in ["v", "<", ">", "^"]:
                start = (i, j)
                direction = interpretation[j][i]

    log.debug(f"{start=} {direction=}")

    total = 0

    for pos in visited:
        grid = interpretation.copy()
        save = grid[pos[1]][pos[0]]
        grid[pos[1]][pos[0]] = "#"
        log.debug(f"Changing {pos}")

        if isInLoop(grid, start, direction, log):
            log.debug(f"{pos=} is looping")
            total += 1

        else:
            log.debug(f"{pos=} is not looping")

        grid[pos[1]][pos[0]] = save

    return total


if __name__ == "__main__":
    DAY = "06"
    DEBUG = False

    structlog.configure(
        wrapper_class=structlog.make_filtering_bound_logger(
            logging.DEBUG if DEBUG else logging.INFO
        ),
    )

    log: structlog.BoundLogger = structlog.get_logger(DAY=DAY)

    log.info(f"Day {DAY}!")

    input: list[str]
    with open(
        f"./data/input" + f"_{DAY}{'_DEBUG' if DEBUG else ''}" + ".txt",
        mode="r",
    ) as f:
        input = f.read().split("\n")

    interpretation = interpretInput(input, log)
    outputPart1, visited = part1(interpretation, log)
    log.info(f"Part 1: {outputPart1}")

    outputPart2 = part2(interpretation, visited, log)
    log.info(f"Part 2: {outputPart2}")
