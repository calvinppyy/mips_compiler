#ifndef command_h
#define command_h

#include <iostream>
#include "scanner.h"

class Command{
public:
    bool hasLabel = false;
    virtual void print() = 0;
    virtual void execute() = 0;
    virtual ~Command(){};
};

class JALR: public Command{
public:
    int line;
    int reg;
    JALR(int line,int reg);
    ~JALR() override;
    void print() override;
    void execute() override;
};

class JR: public Command{
public:
    int line;
    int reg;
    JR(int line,int reg);
    ~JR() override;
    void print() override;
    void execute() override;
};

class ADD: public Command{
public:
    int line;
    int des;
    int s;
    int t;
    ADD(int line, int des, int s, int t);
    ~ADD() override;
    void print() override;
    void execute() override;
};

class SUB: public Command{
public:
    int line;
    int des;
    int s;
    int t;
    SUB(int line, int des, int s, int t);
    ~SUB() override;
    void print() override;
    void execute() override;
};

class SLT: public Command{
public:
    int line;
    int des;
    int s;
    int t;
    SLT(int line, int des, int s, int t);
    ~SLT() override;
    void print() override;
    void execute() override;
};

class SLTU: public Command{
public:
    int line;
    int des;
    int s;
    int t;
    SLTU(int line, int des, int s, int t);
    ~SLTU() override;
    void print() override;
    void execute() override;
};

class BEQ: public Command{
public:
    int line;
    int Pos;
    Token* offset;
    int s;
    int t;
    BEQ(int line, int Pos,Token* offset, int s, int t);
    ~BEQ() override;
    void print() override;
    void execute() override;
};

class BNE: public Command{
public:
    int line;
    int Pos;
    Token* offset;
    int s;
    int t;
    BNE(int line, int Pos,Token* offset, int s, int t);
    ~BNE() override;
    void print() override;
    void execute() override;
};

class LIS: public Command{
public:
    int line;
    int reg;
    LIS(int line,int reg);
    ~LIS() override;
    void print() override;
    void execute() override;
};

class MFHI: public Command{
public:
    int line;
    int reg;
    MFHI(int line,int reg);
    ~MFHI() override;
    void print() override;
    void execute() override;
};

class MFLO: public Command{
public:
    int line;
    int reg;
    MFLO(int line,int reg);
    ~MFLO() override;
    void print() override;
    void execute() override;
};

class WORD: public Command{
public:
    int line;
    Token *operand;
    WORD(int line,Token *operand);
    ~WORD() override;
    void print() override;
    void execute() override;
};

class MULT: public Command{
public:
    int line;
    int s;
    int t;
    MULT(int line, int s, int t);
    ~MULT() override;
    void print() override;
    void execute() override;
};

class MULTU: public Command{
public:
    int line;
    int s;
    int t;
    MULTU(int line, int s, int t);
    ~MULTU() override;
    void print() override;
    void execute() override;
};

class DIV: public Command{
public:
    int line;
    int s;
    int t;
    DIV(int line, int s, int t);
    ~DIV() override;
    void print() override;
    void execute() override;
};

class DIVU: public Command{
public:
    int line;
    int s;
    int t;
    DIVU(int line, int s, int t);
    ~DIVU() override;
    void print() override;
    void execute() override;
};

class LW: public Command{
public:
    int line;
    int s;
    int num;
    int t;
    LW(int line,int s, int num, int t);
    ~LW() override;
    void print() override;
    void execute() override;
};

class SW: public Command{
public:
    int line;
    int s;
    int num;
    int t;
    SW(int line,int s, int num, int t);
    ~SW() override;
    void print() override;
    void execute() override;
};

void output_word(int word);

#endif
