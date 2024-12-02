import logging
import structlog


def interpretInput(input: list[str], log: structlog.BoundLogger):
    reports: list[list[int]] = []
    for line in input:
        strings = line.split(" ")
        report = [int(s) for s in strings]
        reports.append(report)
    return reports


def validate(diffs: list[int]) -> bool:
    valid: bool = True
    asc: bool = diffs[0] >= 0

    for diff in diffs:
        if (diff > 0) and not asc or (diff < 0) and asc:
            return False

        if 1 <= abs(diff) <= 3:
            pass
        else:
            return False

    return valid


def part1(interpretation, log: structlog.BoundLogger) -> int:
    log.debug("Part 1:")
    safeReports: int = 0

    for report in interpretation:
        diffs: list[int] = []
        for a, b in zip(report[:-1], report[1:]):
            diffs.append(b - a)

        log.debug(f"{validate(diffs)}: {diffs}")
        if validate(diffs):
            safeReports += 1

    return safeReports


def part2(interpretation, log: structlog.BoundLogger) -> int:
    log.debug("Part 2:")
    safeReports: int = 0

    for report in interpretation:
        l = len(report)
        for i in range(l):
            pop: int = report.pop(i)
            diffs: list[int] = []
            for a, b in zip(report[:-1], report[1:]):
                diffs.append(b - a)

            log.debug(f"{validate(diffs)}: {diffs}")
            if validate(diffs):
                safeReports += 1

                report.insert(i, pop)
                break

            report.insert(i, pop)

    return safeReports


if __name__ == "__main__":
    DAY = "02"
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
    outputPart1 = part1(interpretation, log)
    outputPart2 = part2(interpretation, log)

    log.info(f"Part 1: {outputPart1}")
    log.info(f"Part 2: {outputPart2}")
