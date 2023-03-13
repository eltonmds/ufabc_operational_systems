from time import sleep
from typing import Tuple, List 
import logging

from process import Process
from mqp import MQP

logging.basicConfig()
logger = logging.getLogger("")
logger.setLevel(logging.INFO)


def create_process(input: Tuple[str]) -> Process:
        process = Process(input[0], int(input[1]), int(input[2]))
        if process.priority not in range(4):
            Exception("Priority must be between 0 and 3")
            pass

        return process


def receive_user_input() -> List[tuple]:
    processes_attributes: List[str] = []

    with open("processes.txt", "r") as processes:
        lines = processes.readlines()
        for line in lines:
            line = line.split(", ")
            processes_attributes.append(tuple(line))

        processes.close()

    return processes_attributes

      
def receive_processes(processes_attributes: List[tuple]) -> MQP:
    mqp: MQP = MQP()
    
    for process_attribute in processes_attributes:
        new_process: Process = create_process(process_attribute)
        logger.info(f"New process created: {new_process.name}")

        mqp.insert_process(new_process)

    return mqp



def select_process(mqp: MQP) -> Process:
    for i in range(4):
        current_priority_level = eval(f"mqp.priority_{i}")
        if current_priority_level:
            chosen_process = mqp.find_smallest_cpu_burst(current_priority_level)
    
            return chosen_process
    else:
        logger.info("No processes to select")
        return None


def main():
    processes_input = receive_user_input()
    mqp = receive_processes(processes_input)

    print("These are the processes received: ")
    mqp.print_processes()

    logger.info("Starting the scheduling process...")

    while not mqp.is_empty():
        current_process = select_process(mqp)
        logger.info("Executing the following process:")
        current_process.print_info()        
        while current_process.CPU_burst > 0:
            current_process.CPU_burst -= 10
            sleep(10)
            mqp.increase_wait_time(current_process)
            mqp.change_smallest_priority_process()

        logger.info(f"Process finished: {current_process.name}\n")
        mqp.remove_process(current_process)
    
    logger.info("All processes terminated")

if __name__ == "__main__":
    main()
