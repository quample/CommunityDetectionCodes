#include "range.hpp"

#include <cassert>

namespace amd {

    std::auto_ptr<range<std::string> > rangeOverStream(std::istream &_istr, const char *_delims /*= "\n"*/) {
        range<std::string> *r = new RangeOverStream(_istr, _delims);
        return std::auto_ptr<range<std::string> >(r);
    }

    void RangeOverStream::nextLine() {
        currentLine = "";
        if (strlen(delims) == 1)
            getline(istr, currentLine, delims[0]);
        else
            while (istr.peek() != EOF) {
                char c = istr.get();
                if (strchr(delims, c))
                    break;
                currentLine.push_back(c);
            }
    }

    RangeOverStream::RangeOverStream(std::istream &_istr, const char *_delims) : istr(_istr), delims(_delims),
                                                                                 isEmpty(false) {
        assert(delims && delims[0]);
        nextLine();
    }

/*virtual*/ bool RangeOverStream::empty() const {
        return isEmpty;
    }

/*virtual*/ std::string RangeOverStream::front() const {
        return currentLine;
    }

/*virtual*/ void RangeOverStream::popFront() {
        if (istr.peek() == EOF) {
            isEmpty = true;
            currentLine = "";
        } else {
            nextLine();
        }
    }

} // namespace amd
