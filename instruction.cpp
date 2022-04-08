#include "instruction.h"
#include <iostream>
#include <bitset>
#include <stdlib.h>
using namespace std;

instruction::instruction(int lineNum, string opCode, string op1, string op2, string op3){
	//Set defaults
	Op = 0b00000001;
	A = op1;
	B = op2;
	Data = op3;
	isData = false;
	Len = 1;
	sourceLine = lineNum;

	//Assign correct OpCode
	//HLT & NOP
	if(opCode == "HLT"){
		Op = 0b00000000;
	}
	else if(opCode == "NOP"){
		Op = 0b00000001;
	}
	//Flags
	else if(opCode == "FSN"){
		Op = 0b00000010;
	}
	else if(opCode == "FCN"){
		Op = 0b00000010;
	}
	else if(opCode == "FSI"){
		Op = 0b00000100;
	}
	else if(opCode == "FSC"){
		Op = 0b00000110;
	}
	else if(opCode == "FCC"){
		Op = 0b00000111;
	}
	else if(opCode == "FCA"){
		Op = 0b00001000;
	}
	//RET & RETI
	else if(opCode == "RET"){
		Op = 0b00001001;
	}
	else if(opCode == "RETI"){
		Op = 0b00001010;
	}
	//Delay
	else if(opCode == "DLY"){
		Op = 0b00001110;
	}
	//Branch
	else if(opCode == "BCS"){
		Op = 0b00010000;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BCC"){
		Op = 0b00010001;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BNS"){
		Op = 0b00010010;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BNC"){
		Op = 0b00010011;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BZS"){
		Op = 0b00010100;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BZC"){
		Op = 0b00010101;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BLT"){
		Op = 0b00010110;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BGE"){
		Op = 0b00010111;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BGT"){
		Op = 0b00011000;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BLE"){
		Op = 0b00011001;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BS1"){
		Op = 0b00011010;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BS2"){
		Op = 0b00011011;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BS3"){
		Op = 0b00011100;
		Len = 2;
		Data = A;
	}
	else if(opCode == "BS4"){
		Op = 0b00011101;
		Len = 2;
		Data = A;
	}
	//INC
	else if(opCode == "INC"){
		//Opcode
		if(A == "AL"){
			Op = 0b00101000;
		}
		else if(A == "AX"){
			Op = 0b00111000;
		}
		else if(A == "RT"){
			Op = 0b00111110;
		}
		else if(A[1] == 'X'){
			Op = 0b00110000;
			Len = 2;
		}
		else if(A[1] == 'H' || A[1] == 'L'){
			Op = 0b00100000;
			Len = 2;
		}
		else{
			error(1);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + "0000";
		}
	}
	//DEC
	else if(opCode == "DEC"){
		//Opcode
		if(A == "AL"){
			Op = 0b00101001;
		}
		else if(A == "AX"){
			Op = 0b00111001;
		}
		else if(A == "RT"){
			Op = 0b00111111;
		}
		else if(A[1] == 'X'){
			Op = 0b00110001;
			Len = 2;
		}
		else if(A[1] == 'H' || A[1] == 'L'){
			Op = 0b00100001;
			Len = 2;
		}
		else{
			error(1);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + "0000";
		}
	}
	//CLR
	else if(opCode == "CLR"){
		//Opcode
		if(A == "AL"){
			Op = 0b00101010;
		}
		else if(A == "AX"){
			Op = 0b00111010;
		}
		else if(A[1] == 'X'){
			Op = 0b00110010;
			Len = 2;
		}
		else if(A[1] == 'H' || A[1] == 'L'){
			Op = 0b00100010;
			Len = 2;
		}
		else{
			error(1);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + "0000";
		}
	}
	//NOT
	else if(opCode == "NOT"){
		//Opcode
		if(A == "AL"){
			Op = 0b00101011;
		}
		else if(A == "AX"){
			Op = 0b00111011;
		}
		else if(A[1] == 'X'){
			Op = 0b00110011;
			Len = 2;
		}
		else if(A[1] == 'H' || A[1] == 'L'){
			Op = 0b00100011;
			Len = 2;
		}
		else{
			error(1);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + "0000";
		}
	}
	//LSL
	else if(opCode == "LSL"){
		//Opcode
		if(A == "AL"){
			Op = 0b00101100;
		}
		else if(A == "AX"){
			Op = 0b00111100;
		}
		else if(A[1] == 'X'){
			Op = 0b00110100;
			Len = 2;
		}
		else if(A[1] == 'H' || A[1] == 'L'){
			Op = 0b00100100;
			Len = 2;
		}
		else{
			error(1);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + "0000";
		}
	}
	//LSR
	else if(opCode == "LSR"){
		//Opcode
		if(A == "AL"){
			Op = 0b00101101;
		}
		else if(A == "AX"){
			Op = 0b00111101;
		}
		else if(A[1] == 'X'){
			Op = 0b00110101;
			Len = 2;
		}
		else if(A[1] == 'H' || A[1] == 'L'){
			Op = 0b00100101;
			Len = 2;
		}
		else{
			error(1);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + "0000";
		}
	}
	//ADD
	else if(opCode == "ADD"){
		//Opcode
		if(A == "BL" && B == "AL"){
			Op = 0b01001000;
		}
		else if(A == "BX" && B == "AX"){
			Op = 0b01011000;
		}
		else if(A[1] == 'X' && B[1] == 'X'){
			Op = 0b01010000;
			Len = 2;
		}
		else if((A[1] == 'H' || A[1] == 'L') && (B[1] == 'H' || B[1] == 'L')){
			Op = 0b01000000;
			Len = 2;
		}
		else{
			error(2);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + RegisterNibble(B);
		}
	}
	//SUB
	else if(opCode == "SUB"){
		//Opcode
		if(A == "BL" && B == "AL"){
			Op = 0b01001001;
		}
		else if(A == "BX" && B == "AX"){
			Op = 0b01011001;
		}
		else if(A[1] == 'X' && B[1] == 'X'){
			Op = 0b01010001;
			Len = 2;
		}
		else if((A[1] == 'H' || A[1] == 'L') && (B[1] == 'H' || B[1] == 'L')){
			Op = 0b01000001;
			Len = 2;
		}
		else{
			error(2);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + RegisterNibble(B);
		}
	}
	//AND
	else if(opCode == "AND"){
		//Opcode
		if(A == "BL" && B == "AL"){
			Op = 0b01001010;
		}
		else if(A == "BX" && B == "AX"){
			Op = 0b01011010;
		}
		else if(A[1] == 'X' && B[1] == 'X'){
			Op = 0b01010010;
			Len = 2;
		}
		else if((A[1] == 'H' || A[1] == 'L') && (B[1] == 'H' || B[1] == 'L')){
			Op = 0b01000010;
			Len = 2;
		}
		else{
			error(2);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + RegisterNibble(B);
		}
	}
	//OR
	else if(opCode == "OR"){
		//Opcode
		if(A == "BL" && B == "AL"){
			Op = 0b01001011;
		}
		else if(A == "BX" && B == "AX"){
			Op = 0b01011011;
		}
		else if(A[1] == 'X' && B[1] == 'X'){
			Op = 0b01010011;
			Len = 2;
		}
		else if((A[1] == 'H' || A[1] == 'L') && (B[1] == 'H' || B[1] == 'L')){
			Op = 0b01000011;
			Len = 2;
		}
		else{
			error(2);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + RegisterNibble(B);
		}
	}
	//XOR
	else if(opCode == "XOR"){
		//Opcode
		if(A == "BL" && B == "AL"){
			Op = 0b01001100;
		}
		else if(A[1] == 'X' && B[1] == 'X'){
			Op = 0b01010100;
			Len = 2;
		}
		else if((A[1] == 'H' || A[1] == 'L') && (B[1] == 'H' || B[1] == 'L')){
			Op = 0b01000100;
			Len = 2;
		}
		else{
			error(2);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + RegisterNibble(B);
		}
	}
	//MOV
	else if(opCode == "MOV"){
		//Opcode
		if(A == "BL" && B == "AL"){
			Op = 0b01001101;
		}
		else if(A == "BX" && B == "AX"){
			Op = 0b01011101;
		}
		else if(A == "DX" && B == "AX"){
			Op = 0b01011100;
		}
		else if(A == "EX" && B == "AX"){
			Op = 0b01011110;
		}
		else if(A == "SP" && B == "AX"){
			Op = 0b01011111;
		}

		else if(A[1] == 'X' && B[1] == 'X'){
			Op = 0b01010101;
			Len = 2;
		}
		else if((A[1] == 'H' || A[1] == 'L') && (B[1] == 'H' || B[1] == 'L')){
			Op = 0b01000101;
			Len = 2;
		}
		else{
			error(2);
		}
		//Register
		if(Len == 2){
			Data = "B" + RegisterNibble(A) + RegisterNibble(B);
		}
	}
	//Data
	else if(opCode == "DAT" || opCode == "DATA"){
		Data = A;
		isData = true;
	}
	else{
		error(3);
	}
}

//Return length of instruction
int instruction::getLength(){
	return Len;
}

//Convert all values to binary
void instruction::convertNum(vector<point> points, int address){
	//Fill Missing Information
	if(A.empty()){
		A = "0";
	}
	if(B.empty()){
		B = "0";
	}
	if(Data.empty()){
		Data = "0";
	}

	A = toBinary(points, A);
	B = toBinary(points, B);
	Data = toBinary(points, Data);
}

//Generate line(s) for instruction
string instruction::writeWord(int &address){
	string out = "";

	//Raw Data
	if(isData){
		out += Data;
		address++;
	}
	//First instruction word
	else{
		out += Op;
		address++;
	//Second instruction word
		if(Len == 2){
			out += Data;
			address++;
		}
	}
	return out;
}

string instruction::RegisterNibble(string reg){
	string nibble = "";
	switch(reg[0]){
	case 'A':
		nibble = "000";
		break;
	case 'B':
		nibble = "001";
		break;
	case 'C':
		nibble = "010";
		break;
	case 'R':
		nibble = "010";
		break;
	case 'D':
		nibble = "011";
		break;
	case 'E':
		nibble = "100";
		break;
	default:
		error(1);
	}
	switch(reg[1]){
	case 'X':
		nibble += '0';
		break;
	case 'H':
		nibble += '0';
		break;
	case 'L':
		nibble += '1';
		break;
	default:
		error(1);
	}
	return nibble;
}

string instruction::toBinary(vector<point> points, string input){
	string output = "";
	if(input[0] == '#'){
		//Memory Location
		int success = 0;
		for(int i=0; i<points.size(); i++){
			if(input == points.at(i).getName()){
				int t = points.at(i).getLocation();
				output = char(t);
				success = 1;
			}
		}
		if(!success){
			error(4);
		}
	}
	else if(input[0] == 'B'){
		//Binary
		output = input.substr(1, input.size());
		int t = strtol(output.c_str(), NULL, 2);
		if(t < 0b100000000){
			output = char(t);
		}
		else{
			error(5);
		}
	}
	else if(input[0] == 'H'){
		//Hexidecimal
		output = input.substr(1, input.size());
		int t = strtol(output.c_str(), NULL, 16);
		if(t < 0b100000000){
			output = char(t);
		}
		else{
			error(5);
		}
	}
	else if(input[0] == 'D'){
		//Decimal
		output = input.substr(1, input.size());
		int t = atoi(output.c_str());
		if(t < 0b100000000){
			output = char(t);
		}
		else{
			error(5);
		}
	}
	else{
		//Decimal (Implicit)
		int t = atoi(input.c_str());
		if(t < 0b100000000){
			output = char(t);
		}
		else{
			error(5);
		}
	}
	return output;
}

void instruction::error(int errNum){
	string errorString = "Error at " + to_string(sourceLine) + " - ";
	switch(errNum){
	case 1:
		errorString += "Invalid register specified";
		break;
	case 2:
		errorString += "Invalid register or register combination specified";
		break;
	case 3:
		errorString += "Invalid OpCode specified";
		break;
	case 4:
		errorString += "Invalid address tag specified";
		break;
	case 5:
		errorString += "Invalid value specified - Must be between D00-D255, H00-HFF, B00000000-B11111111";
		break;
	default:
		errorString += "Unknown error";
		break;
	}
	cout << errorString + "\n";
	exit(errNum);
}
