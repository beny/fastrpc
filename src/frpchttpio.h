/*
 * FILE             $Id: frpchttpio.h,v 1.1 2005-07-19 13:02:53 vasek Exp $
 *
 * DESCRIPTION      HTTP I/O
 *
 * AUTHOR           Vasek Blazek <blazek@firma.seznam.cz>
 *                  Miroslav Talasek <miroslav.talasek@firma.seznam.cz>
 *
 * Copyright (C) Seznam.cz a.s. 2005
 * All Rights Reserved
 *
 * HISTORY
 *          2005-02-07
 *                  First draft.
 *          2005-02-22
 *                  Transformed for FastRPC
 */

#ifndef FRPCHTTPIO_H
#define FRPCHTTPIO_H

#include <frpcplatform.h>

#include <string>
#include <vector>

//#include <frpchttpio.h>
#include <frpchttp.h>

namespace FRPC
{

// forward declaration
//class DataSource_t;
class DataSink_t;

class FRPC_DLLEXPORT HTTPIO_t
{
public:
    inline HTTPIO_t(int fd, int readTimeout, int writeTimeout,
                    int lineSizeLimit, int bodySizeLimit)
            : fd(fd), readTimeout(readTimeout), writeTimeout(writeTimeout),
            lineSizeLimit(lineSizeLimit), bodySizeLimit(bodySizeLimit)
    {}

    static std::vector<std::string> splitBySpace(const std::string &line,
            size_t upto);

    /**
     * @short Return mame and value of item from http header.
     * 
     * @param line item of header
     * @param name name if item
     * @param  value value of item
     * @return 0 succes, !0 error
     */
    static int getHeaderValue(const std::string &line, std::string &name,
                              std::string &value);

    /**
     * @short Read line from socket.
     *
     * @param checkLimit limit check  
     * @return reat line
     */
    std::string readLine(bool checkLimit = false);

    void readHeader(HTTPHeader_t &header);

    long int readChunkSize();

    /**
     * @short Read entity from socket
     *
     * @param header header used to determine content
     * @param data output
     * @param request we are reading: true=request, false=response.
     */
    void readContent(HTTPHeader_t &header, DataSink_t &data,
                     bool request);

    /**
     * @short Read chunked content.
     *
     * @param header header filled by trailer
     * @param data output
     */
    void readChunkedContent(HTTPHeader_t &header, DataSink_t &data);


    /**
     * @short Read block from socket.
     *
     * @param contentLength Exact block size to read (-1=read until conn close).
     * @param data output
     */
    void readBlock(long int contentLength, DataSink_t &data);

    /**
     * @short Send data to socket.
     *
     * @param data pointer to data
     * @param watchForResponse says that sender receive too
     */
    inline void sendData(const std::string &data,
                         bool watchForResponse = false)
    {
        // send string's content
        return sendData(data.data(), data.length(), watchForResponse);
    }

    /** @short Send data to socket.
     *
     * @param data pointer to data
     * @param length  data length 
     * @param watchForResponse says that sender receive too
     */
    void sendData(const char *data, size_t length,
                  bool watchForResponse = false);
    /**
    *    @brief return reference to socket
    */
    inline int& socket()
    {
        return fd;
    }
    inline void setSocket(int fd)
    {
        this->fd = fd;
    }



private:
    int fd;
    int readTimeout;
    int writeTimeout;
    int lineSizeLimit;
    int bodySizeLimit;
};

} // namespace HTTPStorage

#endif // HSTRIO_H
