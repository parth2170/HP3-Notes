# OpenMP Notes

### Parallel Architectures and Programming Models

**Shared Memory**: When all CPUs share a common memory. This is not very scalable as each CPU will access this memory through the same bus. Here the programming models assume that there is a global address space which is visible to all the processors/tasks.
**Distributed Memory**: When each CPU has its own memory and these CPUs are connected through a network, hence the bus is not a bottle neck here. Each task has its own address spcae. Explicit message passing is required to pass and recieve data. (called message passing)

Hybrid Memory systems combine the two architectures

OpenMP is a shared memory programming model and MPI is a message passing programming model.


### Single Processor Architecture

What is a cycle time?
Processors have a clock speed (eg. 1GHz), so the time taken for one cycle (or clock tick) of the processor is called cycle time which is = 1/(clock speed) (i.e. 1/1GHz). 

**Pipelining**: Every program has a stream of instructions. (eg. Instruction Fetch -> Decode -> Operand Fetch ....). Pipelining splits a program into these set of instructions and one instruction is executed in each cycle. For multiple programs, differnt instructions may be exuted in the same cycle. This is also handled by pipelinng?

**Super-Pipeling**(or Super-scalar): is basically parallelization of instructions. It requires multiple-logic units (i.e. more hardware). This is done at run time by the processor.

**VLIW**: (Very Long Instruction Words) is an architecture where the compiler figures out which instructions can be executed parallely. This makes the hardware much simpler in compared to super pipeling. VLIW is faster as its done offline. But it doesn't have a dynamic view of the program.

**Cache**: Smaller and faster memory that sits between the processor and main memory. It improves performance if memory is being accessed in a structured way.

**Memory bandwidth**: Rate at which data can be moved from between the memory and processor. 

A multi-core CPU comprises of **multiple ALUs**, one for each core. Each core has its own registers but all cores share a bus interface.

Each core can have a single, or multiple threads. An OS which supports multi core, percieves each core as a separate processor and a scheduler maps threads/processes to different cores.

Multi-core processors are **MIMD** where different cores execute different threads (Multiple Instructions), operating on different parts of memory (Multiple Data).

### Simultaneous multi-threading 

Permits multiple independent threads to execute
simultaneously on the same core
