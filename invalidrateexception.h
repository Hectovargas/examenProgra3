#ifndef INVALIDRATEEXCEPTION_H
#define INVALIDRATEEXCEPTION_H
#include <QException>

class InvalidRateException : public QException
{
public:
    InvalidRateException(int rate) : m_rate(rate) {}

    int rate() const { return m_rate; }

    void raise() const { throw *this; }

    InvalidRateException *clone() const { return new InvalidRateException(*this); }

    const char *what() const noexcept override
    {
        return qUtf8Printable(errorMessage());
    }

private:
    int m_rate;

    QString errorMessage() const
    {
        return QString("RATE is not a valid number for a review: %1").arg(m_rate);
    }
};

#endif // INVALIDRATEEXCEPTION_H
