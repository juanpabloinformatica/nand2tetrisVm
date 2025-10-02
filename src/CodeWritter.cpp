#include "CodeWritter.hpp"
#include <iostream>
#include <string>
#include "Utilities.hpp"

CodeWritter::CodeWritter()
{
	this->setPopAssemblyTemplate();
	this->setPushAssemblyTemplate();
	this->setArithmeticAssemblyTemplate();
	// Adding init for branching
	this->setWriteLabelTemplate();
	this->setWriteGotoTemplate();
	this->setWriteIfTemplate();
	this->setWriteCallTemplate();

	this->labelCounter = 0;
	this->firstLabelCounter = 0;
	this->continueLabelCounter = 0;
}
void CodeWritter::PatternMgr::addPattern(std::string pattern,
					 std::string replacement)
{
	this->patternMap[pattern] = replacement;
	this->patternInsertionTrack.push_back(pattern);
}
string CodeWritter::newPushAssembly(string memorySegment,
				    int memorySegmentIndex, int var1)
{
	string pushAssemblyInstance = std::string(this->pushAssemblyTemplate);
	if (memorySegmentIndex >= 0) {
		std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, regexOpenDelimeter, "",
			std::regex_constants::format_first_only);
		std::regex regexCloseDelimeter = std::regex(R"(\n\])");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, regexCloseDelimeter, "",
			std::regex_constants::format_first_only);

		std::regex indexRegex = std::regex(R"(\#\#index\#\#)");
		if (memorySegment == "pointer" || memorySegment == "temp" ||
		    memorySegment == "static") {
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, indexRegex,
				std::to_string(0));
		} else {
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, indexRegex,
				std::to_string(memorySegmentIndex));
		}

		std::regex regexDelimeter = std::regex(R"(\[(\n|.*)*?\]\n)");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, regexDelimeter, "",
			std::regex_constants::format_first_only);

	} else {
		// std::cout << pushAssemblyInstance << std::endl;
		std::regex var1Regex = std::regex(R"(\#\#var1\#\#)");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, var1Regex, std::to_string(var1));
		std::regex regexDelimeter =
			std::regex(R"(\[\n@##index##\nD=A\n\]\n)");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, regexDelimeter, "",
			std::regex_constants::format_first_only);
		std::regex regexOpenDelimeter = std::regex(R"(\[)");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, regexOpenDelimeter, "",
			std::regex_constants::format_first_only);
		std::regex regexCloseDelimeter = std::regex(R"(\n\])");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, regexCloseDelimeter, "",
			std::regex_constants::format_first_only);

		std::regex indexRegex = std::regex(R"(\#\#index\#\#)");
		if (memorySegment == "pointer" || memorySegment == "temp" ||
		    memorySegment == "static") {
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, indexRegex,
				std::to_string(0));
		} else {
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, indexRegex,
				std::to_string(-1 * memorySegmentIndex));
		}

		std::regex labelCounterRegex =
			std::regex(R"(\#\#labelCounter\#\#)");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, labelCounterRegex,
			std::to_string(this->labelCounter));
		this->labelCounter++;
		// std::cout << pushAssemblyInstance << std::endl;
	}
	if (memorySegment == "constant") {
		std::cout << "Entering in CONSTANT" << std::endl;
		// std::cout << "here 2" << std::endl;
		std::regex regexDelimeter = std::regex(R"(\[(\n|.)*\]\n)");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, regexDelimeter, "",
			std::regex_constants::format_first_only);
	} else {
		std::regex firstDelimeterRegex = std::regex(R"(\[\n)");
		pushAssemblyInstance = std::regex_replace(
			pushAssemblyInstance, firstDelimeterRegex, "",
			std::regex_constants::format_first_only);
		if (memorySegment == "pointer" || memorySegment == "temp" ||
		    memorySegment == "static") {
			std::cout << "IN:  POINTER | TEMP | STATIC "
				  << std::endl;
			std::regex referencedRegex =
				std::regex(R"(\[\nA=D\+M\nD=M\n\]\n)");
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, referencedRegex, "",
				std::regex_constants::format_first_only);
			std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, regexOpenDelimeter, "",
				std::regex_constants::format_first_only);
			std::regex cleanRegex = std::regex(R"(M\n\]\n\]\n)");
			// std::regex regexCloseDelimeter = std::regex(R"(\n\])");
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, cleanRegex, "M\n",
				std::regex_constants::format_first_only);
			std::regex memorySegmentRegex =
				std::regex(R"(\#\#m_s\#\#)");
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, memorySegmentRegex,
				std::to_string(
					Utility::memorySegmentMap[memorySegment] +
					memorySegmentIndex));
		} else {
			std::cout << "IN NOT :  POINTER | TEMP | STATIC "
				  << std::endl;
			std::regex regexOpenDelimeter = std::regex(R"(\[\n)");
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, regexOpenDelimeter, "",
				std::regex_constants::format_first_only);
			std::regex referencedRegex =
				std::regex(R"(\]\n\[\nD=D\+M\n\]\n\]\n)");
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, referencedRegex, "",
				std::regex_constants::format_first_only);
			std::regex memorySegmentIndexRegex =
				std::regex(R"(\#\#index\#\#)");
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, memorySegmentIndexRegex,
				std::to_string(memorySegmentIndex));
			std::regex memorySegmentRegex =
				std::regex(R"(\#\#m_s\#\#)");
			pushAssemblyInstance = std::regex_replace(
				pushAssemblyInstance, memorySegmentRegex,
				std::to_string(Utility::memorySegmentMap
						       [memorySegment]));
		}
		// std::regex memorySegmentIndexRegex = std::regex(R"(\#\#index\#\#)");
		// pushAssemblyInstance =
		//     std::regex_replace(pushAssemblyInstance, memorySegmentIndexRegex,
		//                        std::to_string(memorySegmentIndex ));
	}
	return pushAssemblyInstance;
}
string CodeWritter ::newPopAssembly(string memorySegment,
				    int memorySegmentIndex, int var1, int var2)
{
	string popAssemblyInstance = string(this->popAssemblyTemplate);
	PatternMgr patternMgr = PatternMgr();
	patternMgr.addPattern(
		R"(\#\#arg1\#\#)",
		std::to_string(Utility::memorySegmentMap[memorySegment]));
	patternMgr.addPattern(R"(\#\#arg2\#\#)",
			      std::to_string(memorySegmentIndex));
	patternMgr.addPattern(R"(\#\#var1\#\#)", std::to_string(var1));
	patternMgr.addPattern(R"(\#\#var2\#\#)", std::to_string(var2));
	popAssemblyInstance =
		this->transformTemplate(patternMgr, popAssemblyInstance, false);
	if (memorySegment == "pointer" || memorySegment == "temp" ||
	    memorySegment == "static") {
		patternMgr.addPattern(R"(\n\[)", "");
		patternMgr.addPattern(R"(\n\])", "");
		patternMgr.addPattern(R"(\[\nD=D\+M\n\]\n)", "");
		popAssemblyInstance = this->transformTemplate(
			patternMgr, popAssemblyInstance, true);
		return popAssemblyInstance;
	}
	patternMgr.addPattern(R"(\n\[\nA=D\+A\nD=A\n\])", "");
	patternMgr.addPattern(R"(\n\[)", "");
	patternMgr.addPattern(R"(\n\])", "");
	popAssemblyInstance =
		this->transformTemplate(patternMgr, popAssemblyInstance, true);
	return popAssemblyInstance;
}
string CodeWritter::_arithmeticAssemblyUnary(string arithmeticType,
					     string arithmeticAssemblyInstance)
{
	PatternMgr patternMgr = PatternMgr();
	patternMgr.addPattern(R"(\n\[)", "");
	patternMgr.addPattern(R"(\n\])", "");
	patternMgr.addPattern(R"(\#\#operation\#\#)",
			      arithmeticType == "not" ? "!" : "-");
	patternMgr.addPattern(R"(\n\])", "");
	patternMgr.addPattern(R"(\n\[(.|\n)*\])", "");
	return this->transformTemplate(patternMgr, arithmeticAssemblyInstance,
				       true);
}
string CodeWritter::transformTemplate(PatternMgr &patternMgr,
				      string assemblyTemplate, bool firstOnly)
{
	for (auto element : patternMgr.patternInsertionTrack) {
		assemblyTemplate =
			firstOnly ?
				std::regex_replace(
					assemblyTemplate, std::regex(element),
					patternMgr.patternMap[element],
					format_first_only) :
				std::regex_replace(
					assemblyTemplate, std::regex(element),
					patternMgr.patternMap[element]);
	}
	return assemblyTemplate;
}
string
CodeWritter::_arithmeticAssemblyBinaryNotBool(string arithmeticType,
					      string arithmeticAssemblyInstance)
{
	std::regex replaceOperation = std::regex(R"(\#\#operation\#\#)");
	std::regex replaceOpenDelimeter = std::regex(R"(\[\n)");
	std::regex replaceCloseDelimeter = std::regex(R"(\]\n)");
	std::regex replaceUnused = std::regex(R"(\[(\n|.)*?\]\n)");
	std::regex replaceUnusedBranching = std::regex(R"(\[(\n|.)*\]\n)");
	std::string operation = "";
	arithmeticAssemblyInstance =
		std::regex_replace(arithmeticAssemblyInstance, replaceUnused,
				   "", format_first_only);
	arithmeticAssemblyInstance =
		std::regex_replace(arithmeticAssemblyInstance,
				   replaceOpenDelimeter, "", format_first_only);
	arithmeticAssemblyInstance = std::regex_replace(
		arithmeticAssemblyInstance, replaceCloseDelimeter, "",
		format_first_only);
	arithmeticAssemblyInstance = std::regex_replace(
		arithmeticAssemblyInstance, replaceUnusedBranching, "");

	if (arithmeticType == "add") {
		operation = "+";
	} else if (arithmeticType == "sub") {
		operation = "-";
	} else if (arithmeticType == "and") {
		operation = "&";
	} else {
		operation = "|";
	}
	arithmeticAssemblyInstance =
		std::regex_replace(arithmeticAssemblyInstance, replaceOperation,
				   operation, format_first_only);
	return arithmeticAssemblyInstance;
}
string
CodeWritter::_arithmeticAssemblyBinaryBool(string arithmeticType,
					   string arithmeticAssemblyInstance)
{
	std::regex replaceOperation = std::regex(R"(\#\#operation\#\#)");
	std::regex replaceOpenDelimeter = std::regex(R"(\[\n)");
	std::regex replaceCloseDelimeter = std::regex(R"(\]\n)");
	std::regex replaceCloseLastDelimeter = std::regex(R"(M\=M\+1\n\]\n)");
	std::regex replaceUnused = std::regex(R"(\[(.|\n)*?\]\n)");
	std::regex replaceContinueLabel =
		std::regex(R"(\#\#continueLabelCounter\#\#)");
	std::regex replaceFirstLabel =
		std::regex(R"(\#\#firstLabelCounter\#\#)");

	arithmeticAssemblyInstance =
		std::regex_replace(arithmeticAssemblyInstance, replaceUnused,
				   "", format_first_only);
	arithmeticAssemblyInstance =
		std::regex_replace(arithmeticAssemblyInstance, replaceUnused,
				   "", format_first_only);
	arithmeticAssemblyInstance =
		std::regex_replace(arithmeticAssemblyInstance,
				   replaceOpenDelimeter, "", format_first_only);
	arithmeticAssemblyInstance = std::regex_replace(
		arithmeticAssemblyInstance, replaceCloseLastDelimeter,
		"M=M+1\n", format_first_only);

	if (arithmeticType == "eq") {
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceOpenDelimeter, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceCloseDelimeter, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceUnused, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceUnused, "",
			format_first_only);

	} else if (arithmeticType == "gt") {
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceUnused, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceOpenDelimeter, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceCloseDelimeter, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceUnused, "",
			format_first_only);

	} else if (arithmeticType == "lt") {
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceUnused, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceUnused, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceOpenDelimeter, "",
			format_first_only);
		arithmeticAssemblyInstance = std::regex_replace(
			arithmeticAssemblyInstance, replaceCloseDelimeter, "",
			format_first_only);
	}
	arithmeticAssemblyInstance = std::regex_replace(
		arithmeticAssemblyInstance, replaceFirstLabel,
		std::to_string(this->firstLabelCounter));
	arithmeticAssemblyInstance = std::regex_replace(
		arithmeticAssemblyInstance, replaceContinueLabel,
		std::to_string(this->continueLabelCounter));
	this->firstLabelCounter++;
	this->continueLabelCounter++;

	if (true) {
		ofstream log = ofstream("./log/CodeWritterLog.txt");
		log << "CodeWritter:" << std::endl;
		log << arithmeticAssemblyInstance << std::endl;
		log.close();
	}

	return arithmeticAssemblyInstance;
}
string CodeWritter::_arithmeticAssemblyBinary(string arithmeticType,
					      string arithmeticAssemblyInstance)
{
	if (arithmeticType == "add" || arithmeticType == "sub" ||
	    arithmeticType == "or" || arithmeticType == "and")
		return _arithmeticAssemblyBinaryNotBool(
			arithmeticType, arithmeticAssemblyInstance);
	return _arithmeticAssemblyBinaryBool(arithmeticType,
					     arithmeticAssemblyInstance);
	return NULL;
}

string CodeWritter::newArithmeticAssembly(string arithmeticType)
{
	string arithmeticAssemblyInstance = this->arithmeticAssemblyTemplate;
	std::regex replace = std::regex(R"(\#\#operation\#\#)");
	if (arithmeticType == "not" || arithmeticType == "neg")
		return _arithmeticAssemblyUnary(arithmeticType,
						arithmeticAssemblyInstance);
	return _arithmeticAssemblyBinary(arithmeticType,
					 arithmeticAssemblyInstance);

	return arithmeticAssemblyInstance;
}
string CodeWritter::newWriteLabel(string label)
{
	string writeLabelInstance = string(this->writeLabelTemplate);
	std::regex regexLabel = std::regex(R"(\#\#LABEL\#\#)");
	writeLabelInstance =
		std::regex_replace(writeLabelInstance, regexLabel, label);
	return writeLabelInstance;
}
string CodeWritter::newWriteGoto(string label)
{
	string writeGotoInstance = string(this->writeGotoTemplate);
	std::regex regexLabel = std::regex(R"(\#\#LABEL\#\#)");
	writeGotoInstance =
		std::regex_replace(writeGotoInstance, regexLabel, label);
	return writeGotoInstance;
}
string CodeWritter::newWriteIf(string label)
{
	string writeIfInstance = string(this->writeIfTemplate);
	std::regex regexLabel = std::regex(R"(\#\#LABEL\#\#)");
	writeIfInstance =
		std::regex_replace(writeIfInstance, regexLabel, label);
	return writeIfInstance;
}
string CodeWritter::newWriteCall(int currentCommandLineNumber, string nArgs,
				 string functionName)
{
	string writeCallInstance = string(this->writeCallTemplate);
	PatternMgr patternMgr = PatternMgr();
	patternMgr.addPattern(R"(\#\#currentCommandLineNumberPlusOne\#\#)",
			      std::to_string(currentCommandLineNumber));
	patternMgr.addPattern(R"(\#\#nArgs\#\#)", nArgs);
	patternMgr.addPattern(R"(\#\#functionName\#\#)", functionName);
	writeCallInstance =
		this->transformTemplate(patternMgr, writeCallInstance, false);

	return writeCallInstance;
}

string CodeWritter::getTemplate(string filename)
{
	std::filesystem::path cwd = std::filesystem::current_path();
	std::filesystem::path filepath =
		cwd.string() + "/" + "templates" + "/" + filename;
	if (!std::filesystem::exists(filepath.string()))
		return "";

	string result = std::string();
	string currentLine;
	std::ifstream file = std::ifstream(filepath);

	while (std::getline(file, currentLine)) {
		result += currentLine;
		result += "\n";
	}
	result.pop_back();
	file.close();
	return result;
}

string CodeWritter::getPushAssembly(string segment, int index, int var1)
{
	return newPushAssembly(segment, index, var1);
}
string CodeWritter::getPopAssembly(string memorySegmentIndex, int index,
				   int var1, int var2)
{
	return newPopAssembly(memorySegmentIndex, index, var1, var2);
}
string CodeWritter::getArithmeticAssembly(string arithmeticType)
{
	return newArithmeticAssembly(arithmeticType);
}

string CodeWritter::getWriteLabelTemplate(string label)
{
	return this->newWriteLabel(label);
}

string CodeWritter::getWriteGotoTemplate(string label)
{
	return this->newWriteGoto(label);
}

string CodeWritter::getWriteIfTemplate(string label)
{
	return this->newWriteIf(label);
}
string CodeWritter::getWriteCallTemplate(int currentCommandLineNumber,
					 string nArgs, string functionName)
{
	return this->newWriteCall(currentCommandLineNumber, nArgs,
				  functionName);

	return NULL;
}
void CodeWritter::setPushAssemblyTemplate(void)
{
	this->pushAssemblyTemplate = this->getTemplate("pushAssembly.txt");
}
void CodeWritter::setPopAssemblyTemplate(void)
{
	this->popAssemblyTemplate = this->getTemplate("popAssembly.txt");
}

void CodeWritter::setArithmeticAssemblyTemplate(void)
{
	this->arithmeticAssemblyTemplate =
		this->getTemplate("arithmeticAssembly.txt");
}
void CodeWritter::setWriteGotoTemplate(void)
{
	this->writeGotoTemplate = this->getTemplate("writeGoto.txt");
}
void CodeWritter::setWriteIfTemplate(void)
{
	this->writeIfTemplate = this->getTemplate("writeIf.txt");
}
void CodeWritter::setWriteLabelTemplate(void)
{
	this->writeLabelTemplate = this->getTemplate("writeLabel.txt");
}
void CodeWritter::setWriteCallTemplate(void)
{
	this->writeCallTemplate = this->getTemplate("writeCall.txt");
}
