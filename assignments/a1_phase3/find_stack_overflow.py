import logging
import math
import pathlib
import re
import subprocess
import sys

logger = logging.getLogger(__name__)
logging.basicConfig(encoding="utf-8", level=logging.INFO)

NUM_THREADS = 1
MAX_RUNTIME = 30
INITIAL_SIZE = 10_000
FINAL_SIZE = 70_000


def stack_overflow(expected_count: int, actual_count: int, actual_runtime: int) -> bool:
    deadline_reached = math.isclose(
        (MAX_RUNTIME * 1e6),
        actual_runtime,
        abs_tol=1000,
    )
    return expected_count != actual_count


def expected_square_count(size: int) -> int:
    return int(size * (size + 1) / 2)


def parse_program_return(program_stdout: str):
    a: str = "Square called"
    b: str = "times"
    i: int = program_stdout.find(a)
    j: int = program_stdout.find(b)

    square_called: str = program_stdout[i + len(a) : j]
    square_count = int(square_called.strip())

    a: str = "ran for"
    b: str = "microseconds"
    i: int = program_stdout.find(a)
    j: int = program_stdout.find(b)

    ran_for: str = program_stdout[i + len(a) : j]
    run_time = int(ran_for.strip())

    logger.debug(f"{square_count=}, {run_time=}")
    return square_count, run_time


def run_iteration(exe: str, size: int):
    logger.debug(f"Running {exe} with arguments {NUM_THREADS} {MAX_RUNTIME} {size}")

    p = subprocess.run(
        [
            exe,
            f"{NUM_THREADS}",
            f"{MAX_RUNTIME}",
            f"{size}",
        ],
        capture_output=True,
    )
    logger.debug("Program run complete")
    if p.returncode != 0:
        return -1, -1

    decoded_output = p.stdout.decode()
    logger.debug(decoded_output)

    square_count, run_time = parse_program_return(decoded_output)
    return square_count, run_time


def find_max_size(exe: str, initial_size: int, final_size: int) -> int:
    run_number = 0
    prev_overflow = False
    max_size = -1
    while initial_size <= final_size:
        run_number += 1
        size = initial_size + (final_size - initial_size) // 2
        square_count, run_time = run_iteration(exe, size)
        if square_count == -1 or run_time == -1:
            logger.info(f"Run {run_number} complete. Non-zero return code")
            overflow = True
        else:
            expected_count = expected_square_count(size)
            overflow = stack_overflow(expected_count, square_count, run_time)
            logger.info(f"Run {run_number} complete. {size=}, {square_count=}, {expected_count=}, {overflow=}")

        if prev_overflow and not overflow:
            prev_overflow = False
            initial_size = size + 1
            max_size = size
        elif overflow:
            final_size = size - 1
            prev_overflow = True
        else:
            initial_size = size + 1
            prev_overflow = False

    return max_size


def main():
    exe: str = sys.argv[1]

    if exe not in ("partA1.exe", "partA2", "partA3"):
        raise ValueError("Invalid command line argument")
    cur_dir = pathlib.Path(__file__).parent
    exe_path = pathlib.Path(cur_dir, exe)
    print(f"Finding the max size for {exe}.\n")
    size = find_max_size(exe_path, INITIAL_SIZE, FINAL_SIZE)
    print()
    if size == -1:
        print("Could not determine size")
    else:
        print(f"Size just before overflow occurs is {size}")


if __name__ == "__main__":
    main()
