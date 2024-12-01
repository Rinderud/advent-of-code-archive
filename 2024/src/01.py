import structlog


def interpretInput(
    lines: list[str], log: structlog.BoundLogger
) -> tuple[list[int], list[int]]:
    leftList: list[int] = []
    rightList: list[int] = []

    for row in lines:
        s = row.split(" ")
        left = int(s[0])
        right = int(s[-1])

        leftList.append(left)
        rightList.append(right)

    leftList.sort()
    rightList.sort()

    return (leftList, rightList)


def part1(leftList: list[int], rightList: list[int], log: structlog.BoundLogger) -> int:
    totalDiff: int = 0

    assert len(leftList) == len(rightList)
    for left, right in zip(leftList, rightList):
        diff = left - right
        log.debug(f"{left-right=}")
        totalDiff += abs(diff)

    return totalDiff


def part2(leftList: list[int], rightList: list[int], log: structlog.BoundLogger) -> int:
    similarity: int = 0
    for left in leftList:
        count: int = 0
        for right in rightList:
            if right == left:
                count += 1

        log.debug(f"{left*count=}")
        similarity += left * count

    return similarity


if __name__ == "__main__":
    DAY = "01"
    DEBUG = False

    log: structlog.BoundLogger = structlog.get_logger(DAY=DAY, DEBUG=DEBUG)

    log.info(f"Day {DAY}!")

    input: list[str]
    with open(
        f"./data/input" + f"_{DAY}{'_DEBUG' if DEBUG else ''}" + ".txt",
        mode="r",
    ) as f:
        input = f.read().split("\n")

    left, right = interpretInput(input, log)
    outputPart1 = part1(left, right, log)
    outputPart2 = part2(left, right, log)

    log.info(f"Part 1: {outputPart1}")
    log.info(f"Part 2: {outputPart2}")
