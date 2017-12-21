/*---------------------------------------------------------------------------

---------------------------------------------------------------------------*/

// Contributor : Harshana
// Last Update : 28/11/2017

/* Remarks ------------------------------------
INIT:
  add start node

ON LOOP:
  check front panel array
  PID follow (and front box check?)
  if its a possible junction,
    set the path that robot came as visited
    add a node
    check how many paths
    if paths == 2,
      goto that path
      set new path as visited
      set node as visited
    if paths > 1,
      select 1 path and go
      set new path as visited
    if paths == 0,
      set node as visited
      turn around and go until unvisited node meets
    ( see if the junction can be used to identify end at a box ? )
---------------------------------------------*/


