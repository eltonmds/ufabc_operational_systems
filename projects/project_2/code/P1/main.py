import numpy as np
import time

num_processes = 5
num_resources = 6

max_matrix = np.random.randint(low=1, high=6, size=(num_processes, num_resources))

alloc_matrix = np.zeros((num_processes, num_resources), dtype=np.int32)

avail_vector = np.random.randint(low=1, high=6, size=num_resources)

req_matrix = np.zeros((num_processes, num_resources), dtype=np.int32)

need_matrix = max_matrix - alloc_matrix

def is_safe(process_id):
    global avail_vector, alloc_matrix, need_matrix
    req = req_matrix[process_id]
    if np.any(req > need_matrix[process_id]):
        print(f"Process {process_id} has exceeded its maximum claim.")
        return False
    if np.any(req > avail_vector):
        print(f"Resources are not available for Process {process_id} to proceed.")
        return False

    alloc_matrix[process_id] += req
    need_matrix[process_id] -= req
    avail_vector -= req

    work_vector = avail_vector.copy()
    finish_vector = np.zeros(num_processes, dtype=np.bool)
    while True:
        found = False
        for i in range(num_processes):
            if not finish_vector[i] and np.all(need_matrix[i] <= work_vector):
                work_vector += alloc_matrix[i]
                finish_vector[i] = True
                found = True
        if not found:
            break
    if np.all(finish_vector):
        print(f"Resources granted to Process {process_id}.")
        return True
    else:
        print(f"Resources cannot be granted to Process {process_id}.")

        alloc_matrix[process_id] -= req
        need_matrix[process_id] += req
        avail_vector += req
        return False

def main() -> None:
    global avail_vector, alloc_matrix, need_matrix
    for i in range(5):
        time.sleep(15)

        new_req = np.random.randint(low=1, high=6, size=num_resources)
        print(f"New request for Process {i}: {new_req}")
        req_matrix[i] = new_req

        if is_safe(i):
            alloc_matrix[i] += new_req
            need_matrix[i] -= new_req
            avail_vector -= new_req

        time.sleep(3)
        released = np.random.randint(low=1, high=6, size=num_resources)
        print(f"Process {i} has finished and released {released} resources.")
        alloc_matrix[i] -= released
        need_matrix[i] += released
        avail_vector += released

if __name__ == "__main__":
    main()
