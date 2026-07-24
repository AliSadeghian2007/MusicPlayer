#include <QApplication>
#include "mainwindow.h"
#include "accountrepository.h"
#include "accountmanager.h"
#include "albumrepository.h"
#include "songrepository.h"
#include "artistmanager.h"
#include "artistrepository.h"
#include "artist.h"

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

    AccountManager accountManager(accountRepository);
    ArtistManager artistManager(albumRepository, songRepository, accountRepository);

    MainWindow w(&accountManager, &artistManager);
    w.show();

    int result = a.exec();

    accountRepository.saveToFile("accounts.txt");
    albumRepository.saveToFile("albums.txt");
    songRepository.saveToFile("songs.txt");

    return result;
}

