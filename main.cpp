#include <QApplication>
<<<<<<< HEAD

=======
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
#include "mainwindow.h"
#include "accountrepository.h"
#include "accountmanager.h"
#include "albumrepository.h"
#include "songrepository.h"
<<<<<<< HEAD
#include "playlistrepository.h"
#include "listenrrepository.h"
#include "artistrepository.h"
#include "artistmanager.h"
#include "listenermanager.h"
=======
#include "artistmanager.h"
#include "artistrepository.h"
#include "artist.h"
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AccountRepository accountRepository;
    AlbumRepository albumRepository;
    SongRepository songRepository;

    accountRepository.loadFromFile("accounts.txt");
    albumRepository.loadFromFile("albums.txt");
    songRepository.loadFromFile("songs.txt");

    ArtistRepository artistRepository(accountRepository);

    accountRepository.loadFromFile("accounts.txt");
    albumRepository.loadFromFile("albums.txt");
    songRepository.loadFromFile("songs.txt");
    playlistRepository.loadFromFile();

    listenrRepository listenerRepository(accountRepository);
    ArtistRepository artistRepository(accountRepository);

    AccountManager accountManager(accountRepository);
    ArtistManager artistManager(albumRepository, songRepository, accountRepository);

<<<<<<< HEAD
    ListenerManager listenerManager(
        artistRepository,
        albumRepository,
        songRepository,
        playlistRepository,
        listenerRepository
        );

    MainWindow w(&accountManager, &artistManager, &listenerManager);
=======
    MainWindow w(&accountManager, &artistManager);
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82
    w.show();

    int result = a.exec();

    accountRepository.saveToFile("accounts.txt");
    albumRepository.saveToFile("albums.txt");
    songRepository.saveToFile("songs.txt");
<<<<<<< HEAD
    playlistRepository.saveToFile();
=======
>>>>>>> 2fccc40054b19ba61911f9680fabb6f92a8c8b82

    return result;
}

