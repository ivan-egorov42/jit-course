#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <cstddef>
#include <vector>
#include <cassert>
#include <unordered_map>

#include "ir/common.h"

namespace builder {

class BasicBlock;

class InstructionOrValue {
public:
    InstructionOrValue() = default;
    InstructionOrValue(Type type) : type(type) {}
    Type get_type()
    {
        return type;
    }

    virtual ~InstructionOrValue() {}

private:
    Type type;
};

class IntValue : public InstructionOrValue {
public:
    IntValue(Type type, int value, BasicBlock *bb) : InstructionOrValue(type), value(value), bb(bb) {}

    int get_value()
    {
        return value;
    }

    void set_value(int v)
    {
        value = v;
    }

private:
    int value;
    BasicBlock *bb;
};

class IntParam : public InstructionOrValue {
public:
    IntParam(Type type, int param, BasicBlock *bb) : InstructionOrValue(type), param(param), bb(bb) {}

    int get_param()
    {
        return param;
    }

    void set_param(int p)
    {
        param = p;
    }

private:
    int param;
    BasicBlock *bb;
};

class Instruction : public InstructionOrValue {
public:
    using Inputs = std::vector<InstructionOrValue *>;
    using Users = std::vector<Instruction *>;

    Instruction() = default;
    Instruction(Type type, size_t id, Instruction *prev, Instruction *next, Opcode opcode, RetType ret_type,
                BasicBlock *bb)
        : InstructionOrValue(type), id(id), prev(prev), next(next), opcode(opcode), ret_type(ret_type), bb(bb)
    {
        inputs.resize(2);
    };
    virtual ~Instruction() = default;

    BasicBlock *get_bb() const
    {
        return bb;
    }
    size_t get_id() const
    {
        return id;
    }
    Opcode get_opcode() const
    {
        return opcode;
    }
    RetType get_ret_type() const
    {
        return ret_type;
    }

    const Inputs &get_inputs() const
    {
        return inputs;
    }
    const Users &get_users() const
    {
        return users;
    }
    Instruction *get_next()
    {
        return next;
    }
    Instruction *get_prev()
    {
        return prev;
    }

    void add_user(Instruction *user)
    {
        if (std::find(users.begin(), users.end(), user) != users.end())
            return;
        users.push_back(user);
    }

    void add_input(InstructionOrValue *input, int index)
    {
        inputs[index] = input;
        if (Instruction *inst = dynamic_cast<Instruction *>(input))
            inst->add_user(this);
    }

    void set_bb(BasicBlock *other)
    {
        bb = other;
    }
    void set_id(size_t other)
    {
        id = other;
    }
    void set_next(Instruction *other)
    {
        next = other;
    }
    void set_prev(Instruction *other)
    {
        prev = other;
    }

private:
    size_t id;
    Instruction *prev;
    Instruction *next;

    Opcode opcode;
    RetType ret_type;
    BasicBlock *bb;

    Inputs inputs;
    Users users;
};

class InstructionSeq {
public:
    Instruction *get_first_inst()
    {
        return first_inst;
    }
    Instruction *get_last_inst()
    {
        return last_inst;
    }

    void seq_add_inst(Instruction *inst)
    {
        assert(!inst->get_prev() && !inst->get_next());

        if (!last_inst) {
            last_inst = inst;
            first_inst = last_inst;
            return;
        }

        last_inst->get_next()->set_prev(inst);
        last_inst->set_next(inst);
        last_inst = inst;
    }

private:
    Instruction *first_inst;
    Instruction *last_inst;
};

class AssignInst : public Instruction {
public:
    AssignInst(Type type, size_t id, Instruction *prev, Instruction *next, Opcode opcode, RetType ret_type,
               BasicBlock *bb)
        : Instruction(type, id, prev, next, opcode, ret_type, bb)
    {
    }
};

class CondInst : public Instruction {
public:
    CondInst(Type type, size_t id, Instruction *prev, Instruction *next, Opcode opcode, RetType ret_type,
             BasicBlock *bb, CondCode cond_code)
        : Instruction(type, id, prev, next, opcode, ret_type, bb), cond_code(cond_code)
    {
    }

private:
    CondCode cond_code;
};

class PhiInst : public Instruction {
public:
    PhiInst(Type type, size_t id, Instruction *prev, Instruction *next, Opcode opcode, RetType ret_type, BasicBlock *bb)
        : Instruction(type, id, prev, next, opcode, ret_type, bb)
    {
    }

    void add_arg(size_t bb_id, InstructionOrValue *arg)
    {
        args[bb_id] = arg;

        if (Instruction *inst = dynamic_cast<Instruction *>(arg))
            inst->add_user(this);
    }

    InstructionOrValue *get_arg(size_t bb_id)
    {
        return args[bb_id];
    }

private:
    std::unordered_map<size_t, InstructionOrValue *> args;
};

}  // namespace builder
#endif  // INSTRUCTION_H