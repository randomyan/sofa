/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2017 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
/*****************************************************************************
* User of this library should read the documentation
* in the messaging.h file.
******************************************************************************/

#include "Message.h"
#include "ConsoleMessageHandler.h"
#include "DefaultStyleMessageFormatter.h"

namespace sofa
{

namespace helper
{

namespace logging
{

ConsoleMessageHandler::ConsoleMessageHandler(MessageFormatter* formatter)
{
    m_formatter = (formatter==0?&DefaultStyleMessageFormatter::getInstance():formatter);
}

void ConsoleMessageHandler::process(Message &m) {
    m_formatter->formatMessage(m, m.type()>=Message::Error ? std::cerr : std::cout ) ;
}

void ConsoleMessageHandler::setMessageFormatter(MessageFormatter* formatter)
{
    m_formatter = formatter;
}

} // logging
} // helper
} // sofa

