#include "command.h"
//LIS///////////////////////
LIS::LIS(int line,int reg):line{line},reg{reg}{}

void LIS::execute(){
    int instr = (reg<<11)|(1<<4)|(1<<2);
    output_word(instr);
}

LIS::~LIS(){}

void LIS::print(){
    std::cout<<"lis $"<< reg<<std::endl;
}

//MFHI///////////////////////
MFHI::MFHI(int line,int reg):line{line},reg{reg}{}

void MFHI::execute(){
    int instr = (reg<<11)|(1<<4);
    output_word(instr);
}

MFHI::~MFHI(){}

void MFHI::print(){
    std::cout<<"mfhi $"<< reg<<std::endl;
}
//MFLO///////////////////////
MFLO::MFLO(int line,int reg):line{line},reg{reg}{}

void MFLO::execute(){
    int instr = (reg<<11)|(1<<4)|2;
    output_word(instr);
}

MFLO::~MFLO(){}

void MFLO::print(){
    std::cout<<"mflo $"<< reg<<std::endl;
}

//WORD///////////////////////
WORD::WORD(int line,Token *operand):line{line},operand{operand}{}

void WORD::print(){
    std::cout<<".word "<< operand->getLexeme()<<std::endl;
}

WORD::~WORD(){
    delete operand;
}

void WORD::execute(){
    long instr = operand->toLong();
    if(instr>=2147483648){
        instr = instr - 2147483648*2;
    }
    output_word(instr);
}

//JR/////////////////////////
JR::JR(int line,int reg):line{line},reg{reg}{}

void JR::print(){
    std::cout<<"jr $"<<reg<<std::endl;
}


void JR::execute(){
    int instr = (reg<<21)|8;
    output_word(instr);
}


JR::~JR(){}
//JALR////////////////////////
JALR::JALR(int line,int reg):line{line},reg{reg}{}

void JALR::print(){
    std::cout<<"jalr $"<<reg<<std::endl;
}


void JALR::execute(){
    int instr = (reg<<21)|9;
    output_word(instr);
}


JALR::~JALR(){}
//ADD/////////////////////////
ADD::ADD(int line, int des, int s, int t):line{line},des{des},s{s},t{t}{}

ADD::~ADD(){}

void ADD::print(){
    std::cout <<"add $"<<des<<",$"<<s<<",$"<<t<<std::endl;
}

void ADD::execute(){
    int instr = (s<<21)|(t<<16)|(des<<11)|(2<<4);
    output_word(instr);
}

//SUB/////////////////////////
SUB::SUB(int line, int des, int s, int t):line{line},des{des},s{s},t{t}{}

SUB::~SUB(){}

void SUB::print(){
    std::cout <<"sub $"<<des<<",$"<<s<<",$"<<t<<std::endl;
}

void SUB::execute(){
    int instr = (s<<21)|(t<<16)|(des<<11)|(2<<4)|2;
    output_word(instr);
}
//SLT/////////////////////////
SLT::SLT(int line, int des, int s, int t):line{line},des{des},s{s},t{t}{}

SLT::~SLT(){}

void SLT::print(){
    std::cout <<"slt $"<<des<<",$"<<s<<",$"<<t<<std::endl;
}

void SLT::execute(){
    int instr = (s<<21)|(t<<16)|(des<<11)|(2<<4)|10;
    output_word(instr);
}

//SLTU/////////////////////////
SLTU::SLTU(int line, int des, int s, int t):line{line},des{des},s{s},t{t}{}

SLTU::~SLTU(){}

void SLTU::print(){
    std::cout <<"sltu $"<<des<<",$"<<s<<",$"<<t<<std::endl;
}

void SLTU::execute(){
    int instr = (s<<21)|(t<<16)|(des<<11)|(2<<4)|11;
    output_word(instr);
}

//BEQ/////////////////////////
BEQ::BEQ(int line, int Pos,Token* offset, int s, int t):line{line},Pos{Pos},offset{offset},s{s},t{t}{}

BEQ::~BEQ(){delete offset;}

void BEQ::print(){
    std::cout <<"beq $"<<s<<",$"<<t<<","<<offset->toLong()<<std::endl;
}

void BEQ::execute(){
    int instr = (1<<28)|(s<<21)|(t<<16)|(offset->toLong()&0xffff);
    output_word(instr);
}

//BNE/////////////////////////
BNE::BNE(int line, int Pos,Token* offset, int s, int t):line{line},Pos{Pos},offset{offset},s{s},t{t}{}

BNE::~BNE(){delete offset;}

void BNE::print(){
    std::cout <<"bne $"<<s<<",$"<<t<<","<<offset->toLong()<<std::endl;
}

void BNE::execute(){
    int instr = (1<<28)|(1<<26)|(s<<21)|(t<<16)|(offset->toLong()&0xffff);
    output_word(instr);
}

//MULT/////////////////////////
MULT::MULT(int line, int s, int t):line{line},s{s},t{t}{}

MULT::~MULT(){}

void MULT::print(){
    std::cout <<"mult $"<<s<<",$"<<t<<std::endl;
}

void MULT::execute(){
    int instr = (s<<21)|(t<<16)|(3<<3);
    output_word(instr);
}
//MULTU/////////////////////////
MULTU::MULTU(int line, int s, int t):line{line},s{s},t{t}{}

MULTU::~MULTU(){}

void MULTU::print(){
    std::cout <<"multu $"<<s<<",$"<<t<<std::endl;
}

void MULTU::execute(){
    int instr = (s<<21)|(t<<16)|(3<<3)|1;
    output_word(instr);
}

//DIV/////////////////////////
DIV::DIV(int line, int s, int t):line{line},s{s},t{t}{}

DIV::~DIV(){}

void DIV::print(){
    std::cout <<"div $"<<s<<",$"<<t<<std::endl;
}

void DIV::execute(){
    int instr = (s<<21)|(t<<16)|(3<<3)|2;
    output_word(instr);
}

//DIVU/////////////////////////
DIVU::DIVU(int line, int s, int t):line{line},s{s},t{t}{}

DIVU::~DIVU(){}

void DIVU::print(){
    std::cout <<"divu $"<<s<<",$"<<t<<std::endl;
}

void DIVU::execute(){
    int instr = (s<<21)|(t<<16)|(3<<3)|3;
    output_word(instr);
}

//LW/////////////////////////
LW::LW(int line, int s,int num, int t):line{line},s{s},num{num},t{t}{}

LW::~LW(){}

void LW::print(){
    std::cout <<"lw $"<<s<<","<<num<<"("<<t<<")"<<std::endl;
}

void LW::execute(){
    int instr = (8<<28)|(3<<26)|(s<<21)|(t<<16)|(num&0xffff);
    output_word(instr);
}

//SW/////////////////////////
SW::SW(int line, int s,int num, int t):line{line},s{s},num{num},t{t}{}

SW::~SW(){}

void SW::print(){
    std::cout <<"sw $"<<s<<","<<num<<"("<<t<<")"<<std::endl;
}

void SW::execute(){
    int instr = (10<<28)|(3<<26)|(s<<21)|(t<<16)|(num&0xffff);
    output_word(instr);
}

//output////////////////
void output_word(int word){
    unsigned char c;
    c = (word>>24) & 0xff;
    std::cout<<c;
    c = (word>>16) & 0xff;
    std::cout<<c;
    c = (word>>8) & 0xff;
    std::cout<<c;
    c = word & 0xff;
    std::cout<<c;
}
