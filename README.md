# Satellite Task Manager

Practice of task manager for satellite operations

## Instructions

- Set the details of your target **tasks** in a file with JSON format. Follow the example file `input/tasks.json`. Also consider:
    - The `key` of each task object must be unique.
    - Include a `name` that describes each task.
    - Itemize the satellite `resources` requested by each task as an array of integer identifiers. Tasks that request a same resource will not be submitted to the same satellite.
    - Quantify the `payoff` of each tasks. The task manager maximizes the total payoff given the available resources.
    - Tasks with the attribute `completed` set to `true` will be ignored by the tasks manager.

- Enumerate the available **satellites** in a file with JSON format. Follow the example file `input/satellite.json`. Also consider:
  - The `key` of each satellite must be unique.
  - Only satellites with the attribute `status` set to `IDLE` will be considered for tasks submission.


- **Compile** the taskManager:
  
`make taskManager`

- **Test** a case:
  
`make test`

- **Input** your specific tasks and satellites via JSON files:

`input/tasks.json`

`input/satellites.json`

- **Run** the task Manager:
  
`./taskManager input/tasks.json input/satellites.json output/tasks.json`

