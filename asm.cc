#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "scanner.h"
#include "command.h"

using namespace std;

void printSymTable(unordered_map<string, int> &symTable){
    for(auto x:symTable){
        cerr<<x.first<<" "<<x.second<<endl;
    }
}

int main() {
    string line;
    int linePos =0;
    int addressPos=0;
    vector<Command*> total;
    unordered_map<string, int> symTable;
    try {
        while (getline(cin, line)) {
            vector<Token> tokenLine = scan(line);
            unsigned int size = tokenLine.size();
            linePos++;
            for (int i = 0;i<size;i++) {
                Token &token = tokenLine.at(i);
                if(token.getKind() == Token::LABEL){//LABEL//////////////////////
                    string name = token.getLexeme();
                    name.pop_back();
                    if(!(('a'<=name[0]&&name[0]<='z')||('A'<=name[0]&&name[0]<='Z'))){
                        for (auto x: total) {
                            delete x;
                        }
                        cerr << "ERROR : Incorrect LABEL"<<endl;
                        return 1;
                    }
                    if(symTable.count(name) == 0){
                        symTable.insert({name,addressPos});
                    } else {
                        for (auto x: total) {
                            delete x;
                        }
                        cerr<<"ERROR : Duplicate Definition of "<<name<<endl;
                        return 1;
                    }
                } else if(token.getKind()==Token::ID){
                    if(token.getLexeme()=="lis"){//LIS///////////////////////////
                        i++;
                        if(i!=size-1){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: lis can only have one argument"<<endl;
                            return 1;
                        }
                        Token &reg = tokenLine.at(i);
                        if(reg.getKind()==Token::REG){
                            int regNum = reg.toLong();
                            if(regNum>=0&&regNum<=31){
                                Command *lis = new LIS(linePos,regNum);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="mfhi"){//MFHI///////////////////////////
                        i++;
                        if(i!=size-1){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: mfhi can only have one argument"<<endl;
                            return 1;
                        }
                        Token &reg = tokenLine.at(i);
                        if(reg.getKind()==Token::REG){
                            int regNum = reg.toLong();
                            if(regNum>=0&&regNum<=31){
                                Command *lis = new MFHI(linePos,regNum);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="mflo"){//MFLO///////////////////////////
                        i++;
                        if(i!=size-1){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: mflo can only have one argument"<<endl;
                            return 1;
                        }
                        Token &reg = tokenLine.at(i);
                        if(reg.getKind()==Token::REG){
                            int regNum = reg.toLong();
                            if(regNum>=0&&regNum<=31){
                                Command *lis = new MFLO(linePos,regNum);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="jr"){//JR////////////////////
                        i++;
                        if(i!=size-1){
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: jr can only have one argument"<<endl;
                            return 1;
                        }
                        Token &val = tokenLine.at(i);
                        if(val.getKind()==Token::REG){
                            long regNum = val.toLong();
                            if(regNum<=31&&regNum>=0){
                                Command *instr = new JR(linePos,regNum);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Register Number is between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: jr can only be followed by a register number"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="jalr"){//JALR////////////////////
                        i++;
                        if(i!=size-1){
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: jalr can only have one argument"<<endl;
                            return 1;
                        }
                        Token &val = tokenLine.at(i);
                        if(val.getKind()==Token::REG){
                            long regNum = val.toLong();
                            if(regNum<=31&&regNum>=0){
                                Command *instr = new JALR(linePos,regNum);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Register Number is between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: jalr can only be followed by a register number"<<endl;
                            return 1;
                        }
                    }else if(token.getLexeme()=="add"){//ADD////////////////////
                        if(i!=size-6){
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: add can only have three arguments"<<endl;
                            return 1;
                        }
                        i++;
                        Token &des = tokenLine.at(i);
                        Token &c1 = tokenLine.at(i+1);
                        Token &s = tokenLine.at(i+2);
                        Token &c2 = tokenLine.at(i+3);
                        Token &t = tokenLine.at(i+4);
                        i+=4;
                        if(des.getKind()==Token::REG&&s.getKind()==Token::REG&&t.getKind()==Token::REG
                           &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long dn = des.toLong();
                            long sn = s.toLong();
                            long tn = t.toLong();
                            if((dn<=31&&dn>=0)&&(sn<=31&&sn>=0)&&(tn<=31&&tn>=0)){
                                Command *instr = new ADD(linePos,dn,sn,tn);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Register Number is between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: add can only be followed by register numbers"<<endl;
                            return 1;
                        }
                    }else if(token.getLexeme()=="sub"){//SUB////////////////////
                        if(i!=size-6){
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: add can only have three arguments"<<endl;
                            return 1;
                        }
                        i++;
                        Token &des = tokenLine.at(i);
                        Token &c1 = tokenLine.at(i+1);
                        Token &s = tokenLine.at(i+2);
                        Token &c2 = tokenLine.at(i+3);
                        Token &t = tokenLine.at(i+4);
                        i+=4;
                        if(des.getKind()==Token::REG&&s.getKind()==Token::REG&&t.getKind()==Token::REG
                           &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long dn = des.toLong();
                            long sn = s.toLong();
                            long tn = t.toLong();
                            if((dn<=31&&dn>=0)&&(sn<=31&&sn>=0)&&(tn<=31&&tn>=0)){
                                Command *instr = new SUB(linePos,dn,sn,tn);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Register Number is between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: add can only be followed by register numbers"<<endl;
                            return 1;
                        }
                    }else if(token.getLexeme()=="slt"){//SLT////////////////////
                        if(i!=size-6){
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: add can only have three arguments"<<endl;
                            return 1;
                        }
                        i++;
                        Token &des = tokenLine.at(i);
                        Token &c1 = tokenLine.at(i+1);
                        Token &s = tokenLine.at(i+2);
                        Token &c2 = tokenLine.at(i+3);
                        Token &t = tokenLine.at(i+4);
                        i+=4;
                        if(des.getKind()==Token::REG&&s.getKind()==Token::REG&&t.getKind()==Token::REG
                           &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long dn = des.toLong();
                            long sn = s.toLong();
                            long tn = t.toLong();
                            if((dn<=31&&dn>=0)&&(sn<=31&&sn>=0)&&(tn<=31&&tn>=0)){
                                Command *instr = new SLT(linePos,dn,sn,tn);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Register Number is between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: add can only be followed by register numbers"<<endl;
                            return 1;
                        }
                    }else if(token.getLexeme()=="sltu"){//SLTU////////////////////
                        if(i!=size-6){
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: add can only have three arguments"<<endl;
                            return 1;
                        }
                        i++;
                        Token &des = tokenLine.at(i);
                        Token &c1 = tokenLine.at(i+1);
                        Token &s = tokenLine.at(i+2);
                        Token &c2 = tokenLine.at(i+3);
                        Token &t = tokenLine.at(i+4);
                        i+=4;
                        if(des.getKind()==Token::REG&&s.getKind()==Token::REG&&t.getKind()==Token::REG
                           &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long dn = des.toLong();
                            long sn = s.toLong();
                            long tn = t.toLong();
                            if((dn<=31&&dn>=0)&&(sn<=31&&sn>=0)&&(tn<=31&&tn>=0)){
                                Command *instr = new SLTU(linePos,dn,sn,tn);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Register Number is between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: add can only be followed by register numbers"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="beq"){//beq////////////////////
                        if(i!=size-6){
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: add can only have three arguments"<<endl;
                            return 1;
                        }
                        i++;
                        Token &offset = tokenLine.at(i+4);
                        Token &c1 = tokenLine.at(i+1);
                        Token &s = tokenLine.at(i);
                        Token &c2 = tokenLine.at(i+3);
                        Token &t = tokenLine.at(i+2);
                        i+=4;
                        if(t.getKind()==Token::REG&&s.getKind()==Token::REG&&offset.getKind()==Token::INT
                           &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long offn = offset.toLong();
                            long sn = s.toLong();
                            long tn = t.toLong();
                            if((sn<=31&&sn>=0)&&(tn<=31&&tn>=0)&&(offn>=-32768&&offn<=32767)){
                                Token *temp = new Token(offset);
                                Command *instr = new BEQ(linePos,addressPos,temp,sn,tn);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Incorrect input number"<<endl;
                                return 1;
                            }
                        } else if(t.getKind()==Token::REG&&s.getKind()==Token::REG&&offset.getKind()==Token::HEXINT
                                  &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long offn = offset.toLong();
                            long sn = s.toLong();
                            long tn = t.toLong();
                            if((sn<=31&&sn>=0)&&(tn<=31&&tn>=0)&&(offn>=0&&offn<=0xffff)){
                                Token *temp = new Token(offset);
                                Command *instr = new BEQ(linePos,addressPos,temp,sn,tn);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Incorrect input number"<<endl;
                                return 1;
                            }
                        } else if(offset.getKind()==Token::ID&&s.getKind()==Token::REG
                                  &&t.getKind()==Token::REG
                                  &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long sn = s.toLong();
                            long tn = t.toLong();
                            Token *temp = new Token(offset);
                            Command *instr = new BEQ(linePos,addressPos,temp,sn,tn);
                            instr->hasLabel = true;
                            total.push_back(instr);
                            addressPos+=4;
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Incorrect usage of BEQ"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="bne"){//BNE////////////////////
                        if(i!=size-6){
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: add can only have three arguments"<<endl;
                            return 1;
                        }
                        i++;
                        Token &offset = tokenLine.at(i+4);
                        Token &c1 = tokenLine.at(i+1);
                        Token &s = tokenLine.at(i);
                        Token &c2 = tokenLine.at(i+3);
                        Token &t = tokenLine.at(i+2);
                        i+=4;
                        if(t.getKind()==Token::REG&&s.getKind()==Token::REG&&offset.getKind()==Token::INT
                           &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long offn = offset.toLong();
                            long sn = s.toLong();
                            long tn = t.toLong();
                            if((sn<=31&&sn>=0)&&(tn<=31&&tn>=0)&&(offn>=-32768&&offn<=32767)){
                                Token *temp = new Token(offset);
                                Command *instr = new BNE(linePos,addressPos,temp,sn,tn);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Incorrect input number"<<endl;
                                return 1;
                            }
                        } else if(t.getKind()==Token::REG&&s.getKind()==Token::REG&&offset.getKind()==Token::HEXINT
                                  &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long offn = offset.toLong();
                            long sn = s.toLong();
                            long tn = t.toLong();
                            if((sn<=31&&sn>=0)&&(tn<=31&&tn>=0)&&(offn>=0&&offn<=0xffff)){
                                Token *temp = new Token(offset);
                                Command *instr = new BNE(linePos,addressPos,temp,sn,tn);
                                total.push_back(instr);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Incorrect input number"<<endl;
                                return 1;
                            }
                        } else if(offset.getKind()==Token::ID&&s.getKind()==Token::REG
                                  &&t.getKind()==Token::REG
                                  &&c1.getKind()==Token::COMMA&&c2.getKind()==Token::COMMA){
                            long sn = s.toLong();
                            long tn = t.toLong();
                            Token *temp = new Token(offset);
                            Command *instr = new BNE(linePos,addressPos,temp,sn,tn);
                            instr->hasLabel = true;
                            total.push_back(instr);
                            addressPos+=4;
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Incorrect usage of BEQ"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="mult"){//MULT///////////////////////////
                        if(i!=size-4){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: mult can only have two argument"<<endl;
                            return 1;
                        }
                        Token &s = tokenLine.at(i+1);
                        Token &c = tokenLine.at(i+2);
                        Token &t = tokenLine.at(i+3);
                        i+=3;
                        if(s.getKind()==Token::REG&&c.getKind()==Token::COMMA&&t.getKind()==Token::REG){
                            int sn = s.toLong();
                            int tn = t.toLong();
                            if((sn>=0&&sn<=31)&&(tn>=0&&tn<=31)){
                                Command *lis = new MULT(linePos,sn,tn);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="multu"){//MULTU///////////////////////////
                        if(i!=size-4){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: multu can only have two argument"<<endl;
                            return 1;
                        }
                        Token &s = tokenLine.at(i+1);
                        Token &c = tokenLine.at(i+2);
                        Token &t = tokenLine.at(i+3);
                        i+=3;
                        if(s.getKind()==Token::REG&&c.getKind()==Token::COMMA&&t.getKind()==Token::REG){
                            int sn = s.toLong();
                            int tn = t.toLong();
                            if((sn>=0&&sn<=31)&&(tn>=0&&tn<=31)){
                                Command *lis = new MULTU(linePos,sn,tn);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="div"){//DIV///////////////////////////
                        if(i!=size-4){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: div can only have two argument"<<endl;
                            return 1;
                        }
                        Token &s = tokenLine.at(i+1);
                        Token &c = tokenLine.at(i+2);
                        Token &t = tokenLine.at(i+3);
                        i+=3;
                        if(s.getKind()==Token::REG&&c.getKind()==Token::COMMA&&t.getKind()==Token::REG){
                            int sn = s.toLong();
                            int tn = t.toLong();
                            if((sn>=0&&sn<=31)&&(tn>=0&&tn<=31)){
                                Command *lis = new DIV(linePos,sn,tn);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="divu"){//DIVU///////////////////////////
                        if(i!=size-4){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: divu can only have two argument"<<endl;
                            return 1;
                        }
                        Token &s = tokenLine.at(i+1);
                        Token &c = tokenLine.at(i+2);
                        Token &t = tokenLine.at(i+3);
                        i+=3;
                        if(s.getKind()==Token::REG&&c.getKind()==Token::COMMA&&t.getKind()==Token::REG){
                            int sn = s.toLong();
                            int tn = t.toLong();
                            if((sn>=0&&sn<=31)&&(tn>=0&&tn<=31)){
                                Command *lis = new DIVU(linePos,sn,tn);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    } else if(token.getLexeme()=="lw"){//LW///////////////////////////
                        if(i!=size-7){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: lw can only have 3 argument"<<endl;
                            return 1;
                        }
                        Token &t = tokenLine.at(i+1);
                        Token &c = tokenLine.at(i+2);
                        Token &num = tokenLine.at(i+3);
                        Token &lp = tokenLine.at(i+4);
                        Token &s = tokenLine.at(i+5);
                        Token &rp = tokenLine.at(i+6);
                        i+=6;
                        if(s.getKind()==Token::REG&&c.getKind()==Token::COMMA&&t.getKind()==Token::REG
                           &&lp.getKind()==Token::LPAREN&&num.getKind()==Token::INT&&rp.getKind()==Token::RPAREN){
                            int sn = s.toLong();
                            int tn = t.toLong();
                            int nn = num.toLong();
                            if((sn>=0&&sn<=31)&&(tn>=0&&tn<=31)&&(nn>=-32768&&nn<=32767)){
                                Command *lis = new LW(linePos,sn,nn,tn);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else if(s.getKind()==Token::REG&&c.getKind()==Token::COMMA&&t.getKind()==Token::REG
                        &&lp.getKind()==Token::LPAREN&&num.getKind()==Token::HEXINT&&rp.getKind()==Token::RPAREN){
                            int sn = s.toLong();
                            int tn = t.toLong();
                            int nn = num.toLong();
                            if((sn>=0&&sn<=31)&&(tn>=0&&tn<=31)&&(nn>=0&&nn<=0xffff)){
                                Command *lis = new LW(linePos,sn,nn,tn);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    }else if(token.getLexeme()=="sw"){//SW///////////////////////////
                        if(i!=size-7){//if no more token
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR: Invalid Syntax: sw can only have 3 argument"<<endl;
                            return 1;
                        }
                        Token &t = tokenLine.at(i+1);
                        Token &c = tokenLine.at(i+2);
                        Token &num = tokenLine.at(i+3);
                        Token &lp = tokenLine.at(i+4);
                        Token &s = tokenLine.at(i+5);
                        Token &rp = tokenLine.at(i+6);
                        i+=6;
                        if(s.getKind()==Token::REG&&c.getKind()==Token::COMMA&&t.getKind()==Token::REG
                           &&lp.getKind()==Token::LPAREN&&num.getKind()==Token::INT&&rp.getKind()==Token::RPAREN){
                            int sn = s.toLong();
                            int tn = t.toLong();
                            int nn = num.toLong();
                            if((sn>=0&&sn<=31)&&(tn>=0&&tn<=31)&&(nn>=-32768&&nn<=32767)){
                                Command *lis = new SW(linePos,sn,nn,tn);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else if(s.getKind()==Token::REG&&c.getKind()==Token::COMMA&&t.getKind()==Token::REG
                        &&lp.getKind()==Token::LPAREN&&num.getKind()==Token::HEXINT&&rp.getKind()==Token::RPAREN){
                            int sn = s.toLong();
                            int tn = t.toLong();
                            int nn = num.toLong();
                            if((sn>=0&&sn<=31)&&(tn>=0&&tn<=31)&&(nn>=0&&nn<=0xffff)){
                                Command *lis = new SW(linePos,sn,nn,tn);
                                total.emplace_back(lis);
                                addressPos+=4;
                            } else {
                                for (auto x: total) {
                                    delete x;
                                }
                                cerr<<"ERROR: Usage: Register number needs to be between 0 to 31"<<endl;
                                return 1;
                            }
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr << "ERROR: missing register number"<<endl;
                            return 1;
                        }
                    }//else///////////////////////
                    else {
                        for (auto x: total) {
                            delete x;
                        }
                        cerr<<"ERROR: Unknown command"<<endl;
                        return 1;
                    }
                } else if(token.getKind() == Token::WORD){//WORD/////////////////
                    i++;
                    if(i!=size-1){//if no more token
                        for (auto x: total) {
                            delete x;
                        }
                        cerr<<"ERROR: Invalid Syntax: missing value for .word"<<endl;
                        return 1;
                    }
                    Token &val = tokenLine.at(i);
                    if(val.getKind()==Token::INT||val.getKind()==Token::HEXINT){
                        long value = val.toLong();
                        if((value>=-2147483648)&&(value<=4294967295)){
                            Token *temp = new Token(val);
                            Command *word = new WORD(linePos,temp);
                            total.emplace_back(word);
                            addressPos+=4;
                        } else {
                            for (auto x: total) {
                                delete x;
                            }
                            cerr<<"ERROR : Arithmetic Overflow!"<<endl;
                            return 1;
                        }
                    } else if(val.getKind()==Token::ID){
                        Token *temp = new Token(val);
                        Command *word = new WORD(linePos,temp);
                        word->hasLabel = true;
                        total.emplace_back(word);
                        addressPos+=4;
                    } else {
                        for (auto x: total) {
                            delete x;
                        }
                        cerr<<"ERROR: Usage: .word value has to be a number or a label"<<endl;
                        return 1;
                    }
                } else {
                    for (auto x: total) {
                        delete x;
                    }
                    cerr<<"ERROR: Invalid Syntax!"<<endl;
                    return 1;
                }
            }
        }
    } catch (ScanningFailure &f) {
        cerr << f.what() << endl;
        
        return 1;
    }
    //Pass Two//////////////////////////////////////////
    int size = total.size();
    for(auto x:total){//check if labels are defined
        if(!x->hasLabel) continue;
        if(dynamic_cast<WORD*>(x)){
            WORD *temp = static_cast<WORD*>(x);
            string name = temp->operand->getLexeme();
            if(symTable.count(name)!=1){
                for (auto y: total) {
                    delete y;
                }
                cerr<<"ERROR : Undefined Label"<<endl;
                return 1;
            } else {
                auto y = symTable.find(name);
                stringstream ss;
                ss << y->second;
                string value = ss.str();
                delete temp->operand;
                temp->operand = new Token(Token::INT,value);
                temp->hasLabel = false;
            }
        } else  if(dynamic_cast<BEQ*>(x)){
            BEQ* temp = static_cast<BEQ*>(x);
            string name = temp->offset->getLexeme();
            if(symTable.count(name)!=1){
                for (auto x: total) {
                    delete x;
                }
                cerr<<"ERROR : Undefined Label"<<endl;
                return 1;
            } else {
                auto y = symTable.find(name);
                int val = y->second;
                int pos = temp->Pos;
                val = (val-pos-4)/4;
                if(val>32767||val<-32768){
                    for (auto y: total) {
                        delete y;
                    }
                    cerr<<"ERROR : val is out of range"<<endl;
                    return 1;
                }
                stringstream ss;
                ss << val;
                string value = ss.str();
                delete temp->offset;
                temp->offset = new Token(Token::INT,value);
                temp->hasLabel = false;
            }
        } else  if(dynamic_cast<BNE*>(x)){
            BNE* temp = static_cast<BNE*>(x);
            string name = temp->offset->getLexeme();
            if(symTable.count(name)!=1){
                for (auto x: total) {
                    delete x;
                }
                cerr<<"ERROR : Undefined Label"<<endl;
                return 1;
            } else {
                auto y = symTable.find(name);
                int val = y->second;
                int pos = temp->Pos;
                val = (val-pos-4)/4;
                if(val>32767||val<-32768){
                    for (auto y: total) {
                        delete y;
                    }
                    cerr<<"ERROR : val is out of range"<<endl;
                    return 1;
                }
                stringstream ss;
                ss << val;
                string value = ss.str();
                delete temp->offset;
                temp->offset = new Token(Token::INT,value);
                temp->hasLabel = false;
            }
        }
    }
    for(auto x:total){
        x->execute();
    }
    printSymTable(symTable);
    for (auto x: total) {
        delete x;
    }
    return 0;
}
