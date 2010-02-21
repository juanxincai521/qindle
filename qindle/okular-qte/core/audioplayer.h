/***************************************************************************
 *   Copyright (C) 2007 by Pino Toscano <pino@kde.org>                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef _OKULAR_AUDIOPLAYER_H_
#define _OKULAR_AUDIOPLAYER_H_

#include <okular/core/okular_export.h>

#include <QtCore/QObject>

namespace Okular {

class AudioPlayerPrivate;
class Document;
class Sound;
class SoundAction;

/**
 * @short An audio player.
 *
 * Singleton utility class to play sounds in documents using the KDE sound
 * system.
 */
class OKULAR_EXPORT AudioPlayer : public QObject
{
    Q_OBJECT

    public:
        ~AudioPlayer();

        /**
         * Gets the instance of the audio player.
         */
        static AudioPlayer * instance();

        /**
         * Enqueue the specified @p sound for playing, optionally taking more
         * information about the playing from the @p soundlink .
         */
        void playSound( const Sound * sound, const SoundAction * linksound = 0 );

        /**
         * Tell the AudioPlayer to stop all the playbacks.
         */
        void stopPlaybacks();

    private:
        AudioPlayer();

        friend class AudioPlayerPrivate;
        AudioPlayerPrivate * const d;
        friend class Document;

        Q_DISABLE_COPY( AudioPlayer )
        Q_PRIVATE_SLOT( d, void finished( int ) )
};

}

#endif

#ifndef _OKULAR_AUDIOPLAYER_P_H_
#define _OKULAR_AUDIOPLAYER_P_H_

// qt/kde includes
#include <qhash.h>
#include <qsignalmapper.h>
#include <QUrl>

class QBuffer;
class PlayData;
class SoundInfo;

namespace Okular {

class AudioPlayer;

class AudioPlayerPrivate
{
public:
    AudioPlayerPrivate( AudioPlayer * qq );

    ~AudioPlayerPrivate();

    int newId() const;
    bool play( const SoundInfo& si );
    void stopPlayings();

    // private slots
    void finished( int );

    AudioPlayer * q;

    QHash< int, PlayData * > m_playing;
    QSignalMapper m_mapper;
    QUrl m_currentDocument;
};

}

#endif
