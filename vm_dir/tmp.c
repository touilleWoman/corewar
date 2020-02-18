#define RAM_SIZE 256
#define MAX_PROCESSES 64
 
typedef struct {
    int pc;
    bool carry;
    char regs[REG_NUMBER][REG_SIZE];
} t_process
 
 
typedef struct {
    char ram[RAM_SIZE]
    t_process processes[MAX_PROCESSES]
} t_vm;
 
 
void run_vm() {
    t_vm vm;
    while (1) {
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (vm->processes[i].active) {
                exec_next_instruction(vm->ram, &vm->processes[i])
            }
        }
    }
}
 
typedef void t_op_dispatch_cb(char *ram, t_process *process);
static t_op_dispatch_cb op_dispatch[] = {
    op_dispatch_live,
    op_dispatch_add,
    op_dispatch_sub,
    // ...
}
 
void op_dispatch_add(char *ram, t_process *process) {
    int pc_offset = 1;
    char params_layout = ram[process->pc + pc_offset]
    pc_offset += 1
    char param1_type = (layout & 0x00001100) >> 2
    char param2_type = (layout & 0x00110000) >> 4
    char param3_type = (layout & 0x11000000) >> 6
 
    int16_t param1_value;
    int16_t param2_value;
    int16_t param3_value;
 
    assert(param1_type == PARAM_REG)
    param1_value = ram[process->pc + pc_offset];
    pc_offset += 1
 
    if (param2_type == PARAM_DIRECT) {
        param2_value = *(uint16_t*)(&ram[process->pc + pc_offset]);
        pc_offset += 2
    } else {
        assert(param2_type == PARAM_REG)
        param2_value = process->regs[ram[process->pc + pc_offset]];
        pc_offset += 1
    }
 
    if (param3_type == PARAM_DIRECT) {
        param3_value = *(uint16_t*)(&ram[process->pc + pc_offset]);
        pc_offset += 2
    } else {
        assert(param3_type == PARAM_REG)
        param3_value = process->regs[ram[process->pc + pc_offset]];
        pc_offset += 1
    }
 
    process->regs[param1_value] = param2_value + param3_value;
 
    process->pc += pc_offset;
}
 
void exec_next_instruction(char *ram, t_process *process) {
    char op = vm->ram[process->pc]
    op_dispatch[op](ram, process)
}
