import structlog

log = structlog.get_logger()
if __name__ == "__main__":
    log.info("Day 01!")

    input: list[str]
    with open("./data/input_01.txt") as f:
        input = f.read().split("\n")

    for i, line in enumerate(input):
        log.debug(f"{i}: {line}")
