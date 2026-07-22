#include "mainwindow.h"
#include <QApplication>

#include "accountrepository.h"
#include "artistrepository.h"
#include "listenrrepository.h"
#include "albumrepository.h"
#include "songrepository.h"
#include "playlistrepository.h"

#include "accountmanager.h"
#include "artistmanager.h"
#include "listenermanager.h"
#include "sharedfeaturesmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AccountRepository accountRepository;
    accountRepository.loadFromFile("accounts.txt");

    ArtistRepository artistRepository(accountRepository);
    listenrRepository listenerRepository(accountRepository);

    AlbumRepository albumRepository;
    SongRepository songRepository;
    PlaylistRepository playlistRepository;

    AccountManager accountManager(accountRepository);
    ArtistManager artistManager(albumRepository, songRepository, accountRepository);
    ListenerManager listenerManager(artistRepository,
                                    albumRepository,
                                    songRepository,
                                    playlistRepository,
                                    listenerRepository);

    SharedFeaturesManager sharedFeaturesManager(songRepository,
                                                albumRepository,
                                                playlistRepository,
                                                accountRepository);

    MainWindow w(&accountManager);
    w.show();

   accountRepository.saveToFile("accounts.txt");

    return a.exec();
}

