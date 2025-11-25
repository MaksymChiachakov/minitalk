# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    minitalk_tester.py                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 03:41:45 by ladloff           #+#    #+#              #
#    Updated: 2024/02/28 21:42:30 by ladloff          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import sys
import psutil
import click
import time
from termcolor import colored
from itertools import cycle

# ----------- PATHS (simplified for your project folder) -----------

PATH_TO_CLIENT = "./client"

# ----------- CONSTANTS -----------

SERVER_NAME = "server"       # only mandatory server
SUCCESS = 0
FAILURE = 1
TIMEOUT_S = 1.0
NEXT_EXEC_TIME_S = 0.2

LIST_COLORS = ["red", "green", "yellow", "blue", "magenta", "cyan"]

# ----------- ERROR STRINGS -----------

ESTR_NO_PROCESS = colored("Error: No process found with name {name}", "red")
ESTR_TIMEOUT = colored(
    "Error: Your project failed to send 100 chars in under 1 second.\n"
    "You do not respect the subject.",
    "red"
)
ESTR_PATH_NOT_EXE = colored("Error: '{path}' is not executable.", "red")
ESTR_PATH_NOT_FILE = colored("Error: '{path}' is not a file.", "red")
ESTR_CPATH_NOT_EXIST = colored("Error: Client path '{path}' does not exist.", "red")

# ----------- TEST MESSAGES -----------

STR_EXEC_TIME = colored("Execution time: {time}s\n", "magenta")

STR_TEST_1 = colored("[Test 1] Sending 100 chars", "green")
STR_TEST_2 = colored("[Test 2] Sending empty string", "green")
STR_TEST_3 = colored("[Test 3] Sending 20,000 chars", "green")
STR_TEST_4 = colored("[Test 4] Stress test: 15x messages of 3000 chars", "green")

# ----------- HEADER -----------

__header__ = r"""
 __  __ ___ _  _ ___ _____ _   _    _  __  _____ ___ ___ _____ ___ ___
|  \/  |_ _| \| |_ _|_   _/_\ | |  | |/ / |_   _| __/ __|_   _| __| _ \
| |\/| || || .` || |  | |/ _ \| |__| ' <    | | | _|\__ \ | | | _||   /
|_|  |_|___|_|\_|___| |_/_/ \_|____|_|\_\   |_| |___|___/ |_| |___|_|_\
                                                              by ladloff
"""

def print_header():
    cycle_colors = cycle(LIST_COLORS)
    for ch in __header__:
        print(colored(ch, next(cycle_colors)), end='')

# ----------- HELPERS -----------

def get_pid(name):
    for process in psutil.process_iter(['pid', 'name']):
        if process.info['name'] == name:
            return process.info['pid']
    print(ESTR_NO_PROCESS.format(name=name))
    return None

def validate_client_path(path):
    if not os.path.exists(path):
        print(ESTR_CPATH_NOT_EXIST.format(path=path))
        sys.exit(FAILURE)
    if not os.path.isfile(path):
        print(ESTR_PATH_NOT_FILE.format(path=path))
        sys.exit(FAILURE)
    if not os.access(path, os.X_OK):
        print(ESTR_PATH_NOT_EXE.format(path=path))
        sys.exit(FAILURE)

def execute_and_measure_time(cmd):
    start = time.time()
    os.system(cmd)
    end = time.time()
    return round(end - start, 2)

# ----------- TESTS -----------

def test_1(server_pid, path):
    print(STR_TEST_1)
    exec_time = execute_and_measure_time(f'{path} {server_pid} {"A" * 100}')
    print(STR_EXEC_TIME.format(time=exec_time))
    if exec_time > TIMEOUT_S:
        print(ESTR_TIMEOUT)
        sys.exit(FAILURE)

def test_2(server_pid, path):
    print(STR_TEST_2)
    exec_time = execute_and_measure_time(f'{path} {server_pid} ""')
    print(STR_EXEC_TIME.format(time=exec_time))

def test_3(server_pid, path):
    print(STR_TEST_3)
    exec_time = execute_and_measure_time(f'{path} {server_pid} {"Y" * 20000}')
    print(STR_EXEC_TIME.format(time=exec_time))

def test_4(server_pid, path):
    print(STR_TEST_4)
    for i in range(15):
        print(colored(f"[Iteration {i+1}]", "light_green"))
        char = chr(97 + i)
        os.system(f'{path} {server_pid} {char * 3000}')
        time.sleep(NEXT_EXEC_TIME_S)
    print()

# ----------- CLI -----------

@click.command()
@click.option('-a', is_flag=True, help="Run all tests")
@click.option('-t1', is_flag=True, help="Run Test 1")
@click.option('-t2', is_flag=True, help="Run Test 2")
@click.option('-t3', is_flag=True, help="Run Test 3")
@click.option('-t4', is_flag=True, help="Run Test 4")
def main(a, t1, t2, t3, t4):
    print_header()

    server_pid = get_pid(SERVER_NAME)
    if server_pid is None:
        sys.exit(FAILURE)

    validate_client_path(PATH_TO_CLIENT)

    tests = [
        (t1 or a, test_1),
        (t2 or a, test_2),
        (t3 or a, test_3),
        (t4 or a, test_4),
    ]

    for should_run, func in tests:
        if should_run:
            func(server_pid, PATH_TO_CLIENT)

if __name__ == "__main__":
    main()
