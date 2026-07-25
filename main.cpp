#include <QApplication>

#include "mainwindow.h"
#include "accountrepository.h"
#include "accountmanager.h"
#include "albumrepository.h"
#include "songrepository.h"
#include "playlistrepository.h"
#include "listenrrepository.h"
#include "artistrepository.h"
#include "artistmanager.h"
#include "listenermanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AccountRepository accountRepository;
    AlbumRepository albumRepository;
    SongRepository songRepository;
    PlaylistRepository playlistRepository;

    accountRepository.loadFromFile("accounts.txt");
    albumRepository.loadFromFile("albums.txt");
    songRepository.loadFromFile("songs.txt");
    playlistRepository.loadFromFile();

    listenrRepository listenerRepository(accountRepository);
    ArtistRepository artistRepository(accountRepository);

    AccountManager accountManager(accountRepository);
    ArtistManager artistManager(albumRepository, songRepository, accountRepository);

    ListenerManager listenerManager(
        artistRepository,
        albumRepository,
        songRepository,
        playlistRepository,
        listenerRepository
        );

    MainWindow w(&accountManager, &artistManager, &listenerManager);
    w.show();

    int result = a.exec();

    accountRepository.saveToFile("accounts.txt");
    albumRepository.saveToFile("albums.txt");
    songRepository.saveToFile("songs.txt");
    playlistRepository.saveToFile();

    return result;
}

