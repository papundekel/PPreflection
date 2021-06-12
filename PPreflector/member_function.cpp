#include "member_function.hpp"

llvm::raw_ostream& PPreflector::operator<<(llvm::raw_ostream& out,
										   clang::Qualifiers cv)
{
	out << "CV::";

	if (cv.hasConst())
	{
		if (cv.hasVolatile())
			out << "const_volatile";
		else
			out << "Const";
	}
	else if (cv.hasVolatile())
		out << "Volatile";
	else
		out << "none";

	return out;
}

llvm::raw_ostream& PPreflector::operator<<(llvm::raw_ostream& out,
										   clang::RefQualifierKind ref)
{
	out << "REF::";

	switch (ref)
	{
		case clang::RefQualifierKind::RQ_None:
			out << "none";
			break;
		case clang::RefQualifierKind::RQ_LValue:
			out << "lvalue";
			break;
		case clang::RefQualifierKind::RQ_RValue:
			out << "rvalue";
			break;
	}

	return out;
}
