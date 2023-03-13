from process import Process
from typing import List
import operator

class MQP:
    def __init__(self) -> None:
        self.priority_0: List[Process] = []
        self.priority_1: List[Process] = []
        self.priority_2: List[Process] = []
        self.priority_3: List[Process] = []
        
    def is_empty(self) -> bool:
        for i in range(4):
            if eval(f"len(self.priority_{i}) > 0"):
                return False
        
        return True

    
    def insert_process(self, process: Process) -> None:
        eval(f"self.priority_{process.priority}.append(process)")
    

    def remove_process(self, process: Process) -> None:
        eval(f"self.priority_{process.priority}.remove(process)")

    
    def increase_priority(self, process: Process) -> None:
        process.priority -= 1
        eval(f"self.priority_{process.priority}.append(process)")
        eval(f"self.priority_{process.priority + 1}.remove(process)")


    def find_biggest_cpu_burst(self, priority_list: List[Process]) -> None:
        priority_list.sort(key=operator.attrgetter("CPU_burst"))
        biggest_process: Process = priority_list[-1]
        return biggest_process
    
    def find_smallest_cpu_burst(self, priority_list: List[Process]) -> None:
        priority_list.sort(key=operator.attrgetter("CPU_burst"))
        biggest_process: Process = priority_list[0]
        return biggest_process


    def change_smallest_priority_process(self) -> None:
        for i in range(3, 0, -1):
            current_level = eval(f"self.priority_{i}")
            if len(current_level) > 0:
                biggest_process = self.find_biggest_cpu_burst(current_level)
                self.increase_priority(biggest_process)
                break

    
    def increase_wait_time(self, current_process: Process) -> None:
        for priority in range(4):
            for process in eval(f"self.priority_{priority}"):
                if process != current_process:
                    process.wait_time += 10


    def print_processes(self) -> None:
        print("  +" + "-" * 15 + "+" + "-" * 8 + "+" + "-" * 9 + "+")
        print(f"  |{'process_name':15}|{'priority':8}|{'CPU_burst':9}|")
        print("  +" + "-" * 15 + "+" + "-" * 8 + "+" + "-" * 9 + "+")

        for i in range(4):
            for process in eval(f"self.priority_{i}"):
                process.print_table()
        
        print("  +" + "-" * 15 + "+" + "-" * 8 + "+" + "-" * 9 + "+\n")

    
