#ifndef ParseBuffer_hxx
#define ParseBuffer_hxx
#include <util/Data.hxx>
#include <util/VException.hxx>

namespace Vocal2
{

class ParseBuffer
{
   public:
      // does NOT OWN the buffer memory
      ParseBuffer(const char* buff, unsigned int len)
         : mBuff(buff),
           mTraversalPtr(buff),
           mEnd(buff+len)
      {}

      class Exception : public VException
      {
         public:
            Exception(const Data& msg, const Data& file, const int line)
               : VException(msg, file, line) {}
            
            const char* name() const { return "ParseBuffer::Exception"; }
      };
      
      // allow the buffer to be rolled back
      void reset(const char* pos);

      bool eof() { return mTraversalPtr >= mEnd;}
      const char* position() { return mTraversalPtr; }
      const char* end() { return mEnd; }

      const char* skipChar() { return ++mTraversalPtr; }
      const char* skipChar(char c);
      const char* skipNonWhitespace();
      const char* skipWhitespace();
      const char* skipToChar(char c);
      const char* skipToOneOf(const char* cs);
      const char* skipToOneOf(const char* cs1, const char* cs2);

      const char* skipToEndQuote(char quote = '"');

      // make the passed in data share memory with the buffer
      void data(Data& data, const char* start) const;

      Data data(const char* start) const;
      
      int integer();
      float floatVal();
      static const char* Whitespace;
      static const char* ParamTerm;
   private:
      ParseBuffer(const ParseBuffer& other);
      ParseBuffer& operator=(const ParseBuffer& other);
      
      const char* mBuff;
      const char* mTraversalPtr;
      const char* mEnd;
};

}

#endif
/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
