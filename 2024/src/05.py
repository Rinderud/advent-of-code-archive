import logging
import structlog


def interpretInput(input: str, log: structlog.PrintLogger):
    sections = input.split("\n\n")

    rules: list[str] = sections[0].splitlines()
    updates: list[list[str]] = [x.split(",") for x in sections[1].splitlines()]

    log.debug(f"{rules=}")
    log.debug(f"{updates=}")

    ruleset: dict[str, set[str]] = {}

    for rule in rules:
        a, b = rule.split("|")
        log.debug(f"{a=} {b=}")

        if a in ruleset.keys():
            ruleset[a].add(b)
        else:
            ruleset[a] = {b}

    log.debug(f"{ruleset=}")

    return (ruleset, updates)


def satisfyRule(
    update: list[str], ruleset: dict[str, set[str]], log: structlog.PrintLogger
) -> bool:
    log.debug(f"{update=}")
    pagesLeft = set(update.copy())
    updateList = update.copy()
    updateList.reverse()

    for page in updateList:
        try:
            rules = ruleset[page]
        except:
            rules = set()

        pagesLeft.remove(page)
        log.debug(f"{page=} {rules=} {rules.intersection(pagesLeft)=}")
        if len(rules.intersection(pagesLeft)) != 0:
            return False

    return True


def part1(interpretation, log: structlog.PrintLogger) -> int:
    ruleset: dict[str, set[str]]
    updates: list[list[str]]
    ruleset, updates = interpretation

    total = 0

    for update in updates:
        valid = satisfyRule(update, ruleset, log)
        log.info(f"{'[x]' if valid else '[ ]'} : {update}")
        if valid:
            middle = int(update[round((len(update) - 1) / 2)])
            log.info(f"\t{middle=}")
            total += middle

    return total


def fix(
    update: list[str], ruleset: dict[str, set[str]], log: structlog.PrintLogger
) -> tuple[list[str], bool]:
    log.debug(f"{update=}")
    pagesLeft = set(update.copy())
    updateList = update.copy()
    updateList.reverse()

    for page in updateList:
        try:
            rules = ruleset[page]
        except:
            rules = set()

        pagesLeft.remove(page)
        intersect = rules.intersection(pagesLeft)
        if len(intersect) != 0:
            log.debug(f"{page} should be before {intersect}")
            i = update.index(page)
            for dependency in intersect:
                newUpdate = update.copy()
                newUpdate.remove(page)
                i = min(i, update.index(dependency))
                newUpdate.insert(i, page)

            return (newUpdate, True)

    return (update, False)


def part2(interpretation, log: structlog.PrintLogger) -> int:
    ruleset: dict[str, set[str]]
    updates: list[list[str]]
    ruleset, updates = interpretation

    total = 0

    for update in updates:
        valid = satisfyRule(update, ruleset, log)
        log.info(f"{'[x]' if valid else '[ ]'} : {update}")
        if not valid:
            change = True
            pageList = update.copy()
            while change:
                pageList, change = fix(pageList, ruleset, log)

            log.info(f"\t{pageList=}")
            middle = int(pageList[round((len(pageList) - 1) / 2)])
            log.info(f"\t\t{middle=}")
            total += middle

    return total


if __name__ == "__main__":
    DAY = "05"
    DEBUG = False

    structlog.configure(
        wrapper_class=structlog.make_filtering_bound_logger(
            logging.DEBUG if DEBUG else logging.INFO
        ),
    )

    log: structlog.PrintLogger = structlog.get_logger(DAY=DAY)

    log.info(f"Day {DAY}!")

    input: str
    with open(
        f"./data/input" + f"_{DAY}{'_DEBUG' if DEBUG else ''}" + ".txt",
        mode="r",
    ) as f:
        input = f.read()

    interpretation = interpretInput(input, log)
    outputPart1 = part1(interpretation, log)
    outputPart2 = part2(interpretation, log)

    log.info(f"Part 1: {outputPart1}")
    log.info(f"Part 2: {outputPart2}")
