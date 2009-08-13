/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtWeb module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/

#include "qxtwebevent.h"
#include "qxtwebcontent.h"
#include <QBuffer>

/*!
\class QxtWebEvent

\inmodule QxtWeb

\brief The QxtWebEvent class is a base class of all QxtWeb event types

QxtWebEvent is the base class for all QxtWeb event classes. Event objects
contain event parameters.

The base QxtWebEvent class contains the type of the event and a session ID for
the session it relates to. Subclasses of QxtWebEvent contain additional
parameters describing the particular event.
*/

/*!
    \enum QxtWebEvent::EventType

    \value None Not an event.
    \value Request A request event.
    \value FileUpload A file upload event.
    \value Page A page event.
    \value StoreCookie A store cookie event.
    \value RemoveCookie A remove cookie event.
    \value Redirect A redirect event.
*/

/*!
 * Constructs a QxtWebEvent of the specified \a type for the specified \a sessionID.
 */
QxtWebEvent::QxtWebEvent(EventType type, int sessionID)
        : sessionID(sessionID), m_type(type) {}

/*!
 * Destroys the event.
 */
QxtWebEvent::~QxtWebEvent() {}

/*!
 * \fn EventType QxtWebEvent::type() const
 * Returns the event type.
 */

/*!
 * \variable QxtWebEvent::sessionID
 * Contains the ID of the session the event is related to.
 */

/*!
\class QxtWebRequestEvent

\inmodule QxtWeb

\brief The QxtWebRequestEvent class describes a request from a web browser

The QxtWebRequestEvent class contains information about a request from a web
browser.
*/

/*!
 * Constructs a QxtWebRequestEvent for the specified \a sessionID, \a requestID and \a url.
 */
QxtWebRequestEvent::QxtWebRequestEvent(int sessionID, int requestID, const QUrl& url)
        : QxtWebEvent(QxtWebEvent::Request, sessionID), requestID(requestID), url(url), originalUrl(url) {}

/*!
 * Destroys the event and any content that may still be associated with it.
 */
QxtWebRequestEvent::~QxtWebRequestEvent()
{
    if (content) delete content;
}

/*!
 * \variable QxtWebRequestEvent::requestID
 * Contains an opaque value generated by the session manager. This request ID
 * must be included in the QxtWebPageEvent or QxtWebPageEvent subclass that
 * is the response to the request.
 */

/*!
 * \variable QxtWebRequestEvent::url
 * Contains the request URL, possibly after rewriting by intermediate services
 * such as QxtWebServiceDirectory.
 */

/*!
 * \variable QxtWebRequestEvent::originalUrl
 * Contains the request URL exactly as it was sent from the web browser.
 */

/*!
 * \variable QxtWebRequestEvent::contentType
 * Contains the MIME type of the request body, if present.
 */

/*!
 * \variable QxtWebRequestEvent::content
 * Contains the content of the request body, if present.
 */

/*!
 * \variable QxtWebRequestEvent::cookies
 * Contains all of the cookies sent by the web browser.
 */

/*!
 * \variable QxtWebRequestEvent::headers
 * Contains all of the headers sent by the web browser.
 *
 * Note that use of these values may not be portable across session maangers.
 */

/*
QxtWebFileUploadEvent::QxtWebFileUploadEvent(int sessionID)
: QxtWebEvent(QxtWebEvent::FileUpload, sessionID) {}
*/

/*!
\class QxtWebErrorEvent

\inmodule QxtWeb

\brief The QxtWebErrorEvent class describes an error condition to be sent to a web browser

The QxtWebErrorEvent class contains information about an error that will be
sent to a web browser.

QxtWebErrorEvent is a QxtWebPageEvent, so the \a dataSource may be replaced
with a custom error page. If you choose to do this, be sure to delete the
original data source automatically generated by the constructor first.
*/

/*!
 * Constructs a QxtWebErrorEvent for the specified \a sessionID and \a requestID,
 * with the provided \a statusCode and \a statusMessage.
 *
 * The requestID is an opaque value generated by the session manager; services
 * will receive this value via QxtWebRequestEvent and must use it in every
 * event that responds to that request.
 */
QxtWebErrorEvent::QxtWebErrorEvent(int sessionID, int requestID, int statusCode, QByteArray statusMessage)
        : QxtWebPageEvent(sessionID, requestID, "<html><body><h1>" + statusMessage + "</h1></body></html>\r\n")
{
    status = statusCode;
    QxtWebPageEvent::statusMessage = statusMessage;
}

/*!
\class QxtWebPageEvent

\inmodule QxtWeb

\brief The QxtWebPageEvent class describes a web page or other content to be sent to a web browser

The QxtWebPageEvent class contains information about a web page or other similar
content that will be sent to a web browser.
*/

/*!
 * Constructs a QxtWebPageEvent for the specified \a sessionID and \a requestID that will
 * use the data from \a source as the content to be sent to the web browser.
 *
 * The requestID is an opaque value generated by the session manager; services
 * will receive this value via QxtWebRequestEvent and must use it in every
 * event that responds to that request.
 *
 * QxtWeb takes ownership of the source and will delete it when the response
 * is completed.
 */
QxtWebPageEvent::QxtWebPageEvent(int sessionID, int requestID, QIODevice* source)
        : QxtWebEvent(QxtWebEvent::Page, sessionID), dataSource(source), chunked(true), streaming(true), requestID(requestID),
        status(200), statusMessage("OK"), contentType("text/html") {}

/*!
 * Constructs a QxtWebPageEvent for the specified \a sessionID and \a requestID that will
 * use \a source as the content to be sent to the web browser.
 *
 * The requestID is an opaque value generated by the session manager; services
 * will receive this value via QxtWebRequestEvent and must use it in every
 * event that responds to that request.
 */
QxtWebPageEvent::QxtWebPageEvent(int sessionID, int requestID, QByteArray source)
        : QxtWebEvent(QxtWebEvent::Page, sessionID), chunked(false), streaming(false), requestID(requestID),
        status(200), statusMessage("OK"), contentType("text/html")
{
    QBuffer* buffer = new QBuffer;
    buffer->setData(source);
    buffer->open(QIODevice::ReadOnly);
    dataSource = buffer;
}

/*!
 * \internal
 */
QxtWebPageEvent::QxtWebPageEvent(QxtWebEvent::EventType typeOverride, int sessionID, int requestID, QByteArray source)
        : QxtWebEvent(typeOverride, sessionID), chunked(false), streaming(false), requestID(requestID),
        status(200), statusMessage("OK"), contentType("text/html")
{
    QBuffer* buffer = new QBuffer;
    buffer->setData(source);
    buffer->open(QIODevice::ReadOnly);
    dataSource = buffer;
}

/*!
 * Destroys the event and any data source attached to it.
 */
QxtWebPageEvent::~QxtWebPageEvent()
{
    if (!dataSource.isNull()) dataSource->deleteLater();
}

/*!
 * \variable QxtWebPageEvent::dataSource
 * Data will be read from this device and relayed to the web browser.
 */

/*!
 * \variable QxtWebPageEvent::chunked
 * If true, and if the web browser supports "chunked" encoding, the content
 * will be sent using "chunked" encoding. If false, or if the browser does not
 * support this encoding (for instance, HTTP/0.9 and HTTP/1.0 user agents),
 * HTTP keep-alive will be disabled.
 *
 * The default value is true when using the QIODevice* constructor and false
 * when using the QByteArray constructor.
 */

/*!
 * \variable QxtWebPageEvent::streaming
 * If true, the data source is considered to be a source of streaming data.
 * The QIODevice must emit the readyRead() signal when data is available and
 * must emit aboutToClose() after all data has been transferred. (This can
 * be accomplished by invoking QIODevice::close() on it after all data is
 * determined to have been transferred.)
 *
 * The default value is true when using the QIODevice* constructor and false
 * when using the QByteArray constructor. If using a QIODevice that does not
 * produce streaming data, such as QFile, this \a must be set to false to
 * ensure correct behavior.
 */

/*!
 * \variable QxtWebPageEvent::requestID
 * Contains the opaque requestID provided by QxtWebRequestEvent.
 */

/*!
 * \variable QxtWebPageEvent::status
 * Contains the HTTP status code that will be sent with the response.
 *
 * The default value is 200 ("OK").
 */

/*!
 * \variable QxtWebPageEvent::statusMessage
 * Contains the human-readable message associated with the HTTP status code
 * that will be sent with the response.
 *
 * The default value is "OK".
 */

/*!
 * \variable QxtWebPageEvent::contentType
 * Contains the MIME type of the content being sent to the web browser.
 *
 * The default value is "text/html".
 */

/*!
\class QxtWebStoreCookieEvent

\inmodule QxtWeb

\brief The QxtWebStoreCookieEvent class describes a cookie to be sent to a web browser

The QxtWebStoreCookieEvent class instructs the session manager to store
a cookie on the web browser.
*/

/*!
 * Constructs a QxtWebStoreCookieEvent for the specified \a sessionID that will
 * store a cookie with the specified \a name and \a data on the web browser.
 *
 * If an \a expiration date is supplied, it will be passed to the browser along
 * with the cookie. The browser will delete the cookie automatically after
 * the specified date. If an expiration date is not supplied, the cookie will
 * expire when the browser is closed.
 */
QxtWebStoreCookieEvent::QxtWebStoreCookieEvent(int sessionID, QString name, QString data, QDateTime expiration)
        : QxtWebEvent(QxtWebEvent::StoreCookie, sessionID), name(name), data(data), expiration(expiration) {}

/*!
 * \variable QxtWebStoreCookieEvent::name
 * Contains the name of the cookie to be stored.
 */

/*!
 * \variable QxtWebStoreCookieEvent::data
 * Contains the content of the cookie to be stored.
 */

/*!
 * \variable QxtWebStoreCookieEvent::expiration
 * Contains the expiration date of the cookie to be stored. If null, the
 * cookie will expire when the web browser is closed.
 */

/*!
\class QxtWebRemoveCookieEvent

\inmodule QxtWeb

\brief The QxtWebRemoveCookieEvent class describes a cookie to be deleted from a web browser

The QxtWebStoreCookieEvent class instructs the session manager to remove
a cookie stored on the web browser.
*/

/*!
 * Constructs a QxtWebRemoveCookieEvent for the specified \a sessionID that
 * removed the cookie with \a name from the web browser.
 */
QxtWebRemoveCookieEvent::QxtWebRemoveCookieEvent(int sessionID, QString name)
        : QxtWebEvent(QxtWebEvent::RemoveCookie, sessionID), name(name) {}

/*!
 * \variable QxtWebRemoveCookieEvent::name
 * Contains the name of the cookie to be removed.
 */

/*!
\class QxtWebRedirectEvent

\inmodule QxtWeb

\brief The QxtWebRedirectEvent class describes a redirect event to be sent to a web browser

The QxtWebRedirectEvent class instructs the web browser to load a page found at
another location.

The default status code, 302, indicates that the requested page was found at
a different location. Other useful status codes are 301, which indicates
that the web browser should always use the new URL in place of the old one,
and (in HTTP/1.1) 307, which indicates that the web browser should reissue
the same request (including POST data) to the new URL.
*/

/*!
 * Constructs a QxtWebRedirectEvent for the specified \a sessionID and \a requestID that
 * instructs the browser to move to the specified \a destination URL with \a statusCode.
 */
QxtWebRedirectEvent::QxtWebRedirectEvent(int sessionID, int requestID, const QString& destination, int statusCode)
        : QxtWebPageEvent(QxtWebEvent::Redirect, sessionID, requestID, QString("Redirect: <a href='%1'>%1</a>").arg(destination).toUtf8()), destination(destination)
{
    QxtWebPageEvent::status = statusCode;
    QxtWebPageEvent::statusMessage = ("Redirect to " + destination).toUtf8();
}

/*!
 * \variable QxtWebRedirectEvent::destination
 * Contains the new location (absolute or relative) to which the browser
 * should redirect.
 */
