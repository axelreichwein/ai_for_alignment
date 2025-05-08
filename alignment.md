# Requirement Aligment Demo

 The following table shows the aligment found by ProductMap between the Requirements provided and the implemented Features of the repository




| Req. ID  | Title              | Criterion               | Status | Explanation  | Feature |
| -------- | ------------------ | ----------------------- | ------ | ------------ | ------- |
| RQ-12    | Obstacle Detection | The system shall detect obstacles within 10 m of the vehicle and measure their speed. | MATCH  | Feature cover the requirement in 2nd level | Find the nearest obstacle within range - Processes a vector of sensor readings to identify the reading corresponding to the closest obstacle, but only considering obstacles within a predefined maximum range. |
| RQ-34    | Speed Detection | The system shall detect maximum speed of the vehicle at 80 km/h. | PARTIAL MATCH  | Feature detect speeds less than 70 km/h | Detect speed of the vehicule - Processes the sensor to get the speed, speed it is up to 70 km/h. |
| RQ-45    | ABS Operation | The system shall detect the break operation to use the ABS. | NO MATCH  |  |  |



