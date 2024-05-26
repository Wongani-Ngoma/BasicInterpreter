# BasicInterpreter
Another challenge on the book "Programming Challenges" by Steven S Skiena and Miguel A Revilla, it's a sort of interpreter that does very basic things: move stuff in memory and registers, not the actuall ones in the cpu, but just normal ram pretending to be registers, and some arithmetic on the registers.

## How to use
- Here are the commands it supports:

| Command | What it does |
|---------|----------------|
| 100     | halt |
| 2dn     | set register d to n(between 0 and 9) |
| 3dn     | add n to register d |
| 4dn     | multiply register d by n |
| 5ds     | set register d to the value of register s|
| 6ds     | add the value of register s to register d |
| 7ds     | multiply register d by the value of register s |
| 8da     | set register d to the value in RAM whose address is in register a |
| 9sa     | set the value in RAM whose address is in register a to that of register s |
| 0ds     | goto the location in register d unless register s contains 0 |
