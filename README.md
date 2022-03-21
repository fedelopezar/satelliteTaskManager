# Satellite Task Manager

Simulator of task manager for satellite operations.

---

The software takes as input a set of target tasks and available satellites, and
distributes such tasks to the satellite constellation.

The submission process to each satellite is done in parallel threads.

Since each task occupies specific resources in the satellite, resources might not be enough and it might not be possible to submit every task. 

The decision-making of which tasks to prioritize
is based on the payoff of each task; the software is designed to maximize the
total payoff, given the available resources.

The actual task realization is simulated by waiting a random number of seconds between
0 and 5, and the probability of success is 10%.

In the end, the software outputs an update of the status of each task. This output file serves as an input for a new set of submissions.

---

## Instructions

- Set the details of your target **tasks** in a JSON file. Follow the example file `input/tasks.json`. Consider:
    - The `key` of each task object must be unique. If there are repeated keys, only the last will be considered.
    - Include a `name` that describes each task.
    - Itemize the satellite `resources` requested by each task as an array of integer identifiers. The tasks that request a same resource will not be submitted to the same satellite.
    - Quantify the `payoff` of each tasks. The task manager will maximize the total payoff,  given the available resources.
    - The tasks with the attribute `completed` set to `true` will be ignored by the task manager.

- Enumerate the available **satellites** in a JSON file. Follow the example file `input/satellite.json`. Consider:
  - The `key` of each satellite must be unique. If there are repeated keys, only the last will be considered.
  - Only satellites with the attribute `status` set to `IDLE` will be considered for tasks submission.


- **Compile** the taskManager:
    - `make taskManager`

- **Test** a case:
    - `make test`


- **Run** the task Manager with your specific input tasks, input satellites, and output file, as arguments:
  - `./taskManager input/tasks.json input/satellites.json output/tasks.json`

- If some tasks failed, and want to re-submit them, **re-run** using the latest output file as input.
  
