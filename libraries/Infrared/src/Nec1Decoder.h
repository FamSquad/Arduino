#ifndef NEC1DECODER_H
#define	NEC1DECODER_H

#include "IrDecoder.h"
#include "IrReader.h"

/**
 * A decoder class for NEC1 signals.
 */
class Nec1Decoder : public IrDecoder {
private:
    static const microseconds_t timebase = 564;
    static const microseconds_t timebaseUpper = 650;
    static const microseconds_t timebaseLower = 450;

    // NOTE: use a signed type to be able to return the value invalid.
    int F;
    int D;
    int S;
    bool ditto;

    char decode[17];

    static boolean getDuration(microseconds_t duration, unsigned int time) {
        return duration <= time * timebaseUpper
                && duration >= time * timebaseLower;
    }
    static int decodeParameter(const IrReader &irCapturer, unsigned int index);
    static int decodeFlashGap(microseconds_t flash, microseconds_t gap);

public:
    Nec1Decoder();

    /**
     * Constructs a Nec1Decoder from an IrReader, containing data.
     * @param irReader IrReader with data, i.e. with isReady() true.
     */
    Nec1Decoder(const IrReader& irReader);
    virtual ~Nec1Decoder() {};

    /**
     * Returns the F parameter, or -1 if invalid.
     * @return int
     */
    int getF() const {
        return F;
    }

    /**
     * Returns the D parameter, or -1 if invalid.
     * @return int
     */
    int getD() const {
        return D;
    }

    /**
     * Returns the S parameter, or -1 if invalid.
     * @return int
     */
    int getS() const {
        return S;
    }

    /**
     * Returns true if the signal received is a NEC1 ditto, i,e. a repeat sequence.
     * @return true if repeat sequence
     */
    boolean isDitto() const {
        return ditto;
    };

    /**
     * Convenience function; constructs an Nec1Decoder and calls its printDecode.
     * @param irReader IrReader to use
     * @param stream Stream
     * @return success of operation
     */
    static boolean tryDecode(const IrReader &irReader, Stream& stream);

    const char *getDecode() const {
        return decode;
    };

};

#endif	/* NEC1DECODER_H */
