/* ----------------------------------------------------------------------- */
/*                                                                         */
/* [konsole.h]                      Konsole                                   */
/*                                                                            */
/* -------------------------------------------------------------------------- */
/*                                                                            */
/* Copyright (c) 1997,1998 by Lars Doelle <lars.doelle@on-line.de>            */
/*                                                                            */
/* This file is part of Konsole, an X terminal.                               */
/*                                                                            */
/* The material contained in here more or less directly orginates from        */
/* kvt, which is copyright (c) 1996 by Matthias Ettrich <ettrich@kde.org>     */
/*                                                                            */
/* -------------------------------------------------------------------------- */

#ifndef KONSOLE_H
#define KONSOLE_H


#include <kmainwindow.h>
#include <kdialogbase.h>
#include <ksimpleconfig.h>
#include <kaction.h>
#include <kpopupmenu.h>
#include <keditcl.h>

#include <kwinmodule.h>

#include <qstrlist.h>
#include <qintdict.h>
#include <qptrdict.h>

#include "TEPty.h"
#include "TEWidget.h"
#include "TEmuVt102.h"
#include "session.h"
#include "schema.h"
#include "konsole_child.h"
#include "konsolebookmarkmenu.h"
#include "konsolebookmarkhandler.h"

#include "konsoleiface.h"

#undef PACKAGE
#undef VERSION
#define PACKAGE "konsole"
#define VERSION "1.2.3"

class KRootPixmap;
class QCheckBox;
class KonsoleFind;

// Defined in main.C
const char *konsole_shell(QStrList &args);

class Konsole : public KMainWindow, virtual public KonsoleIface
{
    Q_OBJECT

    friend class KonsoleSessionManaged;
public:

  Konsole(const char * name, const QString &_program, QStrList & _args, int histon,
    bool menubaron, bool toolbaron, bool frameon, bool scrollbaron, const QString &icon, const QString &_title, 
    QCString type = 0, const QString &_term=QString::null, bool b_inRestore = false, const QString &workdir=QString::null);
  ~Konsole();
  void setColLin(int columns, int lines);
  void setFullScreen(bool on);
  void setAutoClose(bool on);
  void initFullScreen();
  void initSessionFont(int fontNo);
  void initSessionTitle(const QString &_title);
  void initSessionKeyTab(const QString &keyTab);
  void initMonitorActivity(bool on);
  void initMonitorSilence(bool on);
  void initMasterMode(bool on);
  void newSession(const QString &program, const QStrList &args, const QString &term, const QString &icon, const QString &cwd);
  void setSchema(const QString & path);
  
  void enableFullScripting(bool b);

  void run();
  void setDefaultSession(const QString &filename);
  void showTipOnStart();

  // Additional functions for DCOP
  int sessionCount() { return sessions.count(); }

  QString currentSession();
  QString newSession(const QString &type);
  QString sessionId(const int position);

  void activateSession(const QString& sessionId);
  void feedAllSessions(const QString &text);
  void sendAllSessions(const QString &text);

  KURL baseURL() const;

  virtual bool processDynamic(const QCString &fun, const QByteArray &data, QCString& replyType, QByteArray &replyData);
  virtual QCStringList functionsDynamic();

  void callReadPropertiesInternal(KConfig *config, int number) { readPropertiesInternal(config,number); }

public slots:
  void activateSession(int position);

  void makeGUI();
  QString newSession();

protected:

 bool queryClose();
 void saveProperties(KConfig* config);
 void readProperties(KConfig* config);

 

private slots:
  void currentDesktopChanged(int desk);
  void slotBackgroundChanged(int desk);
  void configureRequest(TEWidget*,int,int,int);
  void activateSession();
  void activateSession(TESession*);
  void closeCurrentSession();
  void doneChild(KonsoleChild*, TESession*);
  void doneSession(TESession*);
  void slotCouldNotClose();
  void slotToggleFullscreen();
  void schema_menu_activated(int item);
  void pixmap_menu_activated(int item);
  void keytab_menu_activated(int item);
  void schema_menu_check();
  void attachSession(TESession*);
  void detachSession();
  void bookmarks_menu_check();
  void newSession(int kind);
  void newSessionToolbar(int kind);
  void updateSchemaMenu();
  void updateKeytabMenu();

  void changeColumns(int);
  void notifySessionState(TESession* session,int state);
  void notifySize(int,int);
  void updateTitle();
  void prevSession();
  void nextSession();
  void activateMenu();
  void moveSessionLeft();
  void moveSessionRight();
  void allowPrevNext();
  void setSchema(int n);
  void sendSignal(int n);
  void slotClearTerminal();
  void slotResetClearTerminal();
  void slotToggleToolbar();
  void slotToggleMenubar();
  void slotRenameSession();
  void slotRenameSession(int);
  void slotRenameSession(TESession* ses, const QString &name);
  void slotToggleMonitor();
  void slotToggleMasterMode();
  void slotClearAllSessionHistories();
  void slotHistoryType();
  void slotClearHistory();
  void slotFindHistory();
  void slotSaveHistory();
  void slotSelectBell();
  void slotSelectSize();
  void slotSelectFont();
  void slotSelectScrollbar();
  void loadScreenSessions();

  void slotSaveSettings();
  void slotSaveSessionsProfile();
  void slotConfigureKeys();
  void slotConfigure();
  void reparseConfiguration();

  void clearAllListenToKeyPress();
  void restoreAllListenToKeyPress();
  void enterURL( const QString&, const QString& );
  void newSession( const QString&, const QString& );

  void slotFind();
  void slotFindDone();
  void slotFindNext();
  void slotFindPrevious();

  void fontNotFound();
  void showTip();

  void listSessions();
  void switchToSession1() { activateSession(1); }
  void switchToSession2() { activateSession(2); }
  void switchToSession3() { activateSession(3); }
  void switchToSession4() { activateSession(4); }
  void switchToSession5() { activateSession(5); }
  void switchToSession6() { activateSession(6); }
  void switchToSession7() { activateSession(7); }
  void switchToSession8() { activateSession(8); }
  void switchToSession9() { activateSession(9); }
  void switchToSession10() { activateSession(10); }
  void switchToSession11() { activateSession(11); }
  void switchToSession12() { activateSession(12); }

  void biggerFont();
  void smallerFont();

  void slotPrint();

private:
  KSimpleConfig *defaultSession();
  QString newSession(KSimpleConfig *co, QString pgm = QString::null, const QStrList &args = QStrList(), const QString &_term = QString::null, const QString &_icon = QString::null, const QString &_title = QString::null, const QString &_cwd = QString::null);
  void readProperties(KConfig *config, const QString &schema, bool globalConfigOnly);
  void applySettingsToGUI();
  void makeBasicGUI();
  void runSession(TESession* s);
  void addSession(TESession* s);
  void setColorPixmaps();

  void setSchema(ColorSchema* s);
  void setFont(int fontno);

  void clearSessionHistory(TESession & session);
  void buildSessionMenus();
  void addSessionCommand(const QString & path);
  void loadSessionCommands();
  void addScreenSession(const QString & path, const QString & socket);
  void resetScreenSessions();

  QPtrDict<TESession> action2session;
  QPtrDict<KRadioAction> session2action;
  QPtrDict<KToolBarButton> session2button;
  QPtrList<TESession> sessions;
  QPtrList<KonsoleChild> detached;
  QIntDict<KSimpleConfig> no2command;
  QIntDict<KTempFile> no2tempFile;
  QIntDict<QString> no2filename;
  KSimpleConfig* m_defaultSession;
  QString m_defaultSessionFilename;

  TEWidget*      te;
  TESession*     se;
  TESession*     se_previous;
  TESession*     m_initialSession;
  ColorSchemaList* colors;

  KRootPixmap*   rootxpm;
  KWinModule*    kWinModule;

  KMenuBar*   menubar;
  KStatusBar* statusbar;

  KPopupMenu* m_session;
  KPopupMenu* m_edit;
  KPopupMenu* m_view;
  KPopupMenu* m_bookmarks;
  KPopupMenu* m_bookmarksSession;
  KPopupMenu* m_options;
  KPopupMenu* m_schema;
  KPopupMenu* m_keytab;
  KPopupMenu* m_toolbarSessionsCommands;
  KPopupMenu* m_signals;
  KPopupMenu* m_help;
  KPopupMenu* m_rightButton;

  KToggleAction *monitorActivity;
  KToggleAction *monitorSilence;
  KToggleAction *masterMode;
  KToggleAction *showToolbar;
  KToggleAction *showMenubar;
  KToggleAction *showScrollbar;
  KToggleAction *m_fullscreen;

  KSelectAction *selectSize;
  KSelectAction *selectFont;
  KSelectAction *selectScrollbar;
  KSelectAction *selectBell;

  KAction       *m_clearHistory;
  KAction       *m_findHistory;
  KAction       *m_findNext;
  KAction       *m_findPrevious;
  KAction       *m_saveHistory;
  KAction       *m_detachSession;
  KAction       *m_moveSessionLeft;
  KAction       *m_moveSessionRight;

  KAction       *m_copyClipboard;
  KAction       *m_pasteClipboard;
  KAction       *m_clearTerminal;
  KAction       *m_resetClearTerminal;
  KAction       *m_clearAllSessionHistories;
  KAction       *m_renameSession;
  KAction       *m_saveProfile;
  KAction       *m_closeSession;
  KAction       *m_print;
  KAction       *m_quit;

  KActionCollection *m_shortcuts;

  KonsoleBookmarkHandler *bookmarkHandler;
  KonsoleBookmarkHandler *bookmarkHandlerSession;

  KonsoleFind* m_finddialog;
  bool         m_find_first;
  bool         m_find_found;
  QString      m_find_pattern;

  int cmd_serial;
  int cmd_first_screen;
  int         n_keytab;
  int         n_defaultKeytab;
  int         n_font;
  int         n_defaultFont; // font as set in config to use as default for new sessions
  int         n_scroll;
  int         n_bell;
  int         n_render;
  int         curr_schema; // current schema no
  int         wallpaperSource;
  int         sessionIdCounter;
  int         monitorSilenceSeconds;

  QString     s_schema;
  QString     s_kconfigSchema;
  QString     s_word_seps;			// characters that are considered part of a word
  QString     pmPath; // pixmap path
  QString     dropText;
  QString     fontNotFound_par;
  QFont       defaultFont;
  QSize       defaultSize;

  QRect       _saveGeometry;

  QTimer      m_closeTimeout;

  bool        b_framevis:1;
  bool        b_fullscreen:1;
  bool        m_menuCreated:1;
  bool        skip_exit_query:1;
  bool        b_warnQuit:1;
  bool        isRestored:1;
  bool        b_allowResize:1;
  bool        b_addToUtmp:1;
  bool        b_xonXoff:1;

  bool        b_histEnabled:1;
  bool        b_fullScripting:1;
  unsigned int m_histSize;
};

class QSpinBox;

class HistoryTypeDialog : public KDialogBase
{
    Q_OBJECT
public:
  HistoryTypeDialog(const HistoryType& histType,
                    unsigned int histSize,
                    QWidget *parent);

public slots:

  void slotHistEnable(bool);
  void slotDefault();
  void slotSetUnlimited();

  unsigned int nbLines() const;
  bool isOn() const;

protected:
  QSpinBox*      m_size;
  QCheckBox*     m_btnEnable;
  QPushButton*   m_setUnlimited;
};

class SizeDialog : public KDialogBase
{
    Q_OBJECT
public:
  SizeDialog(unsigned int const columns,
             unsigned int const lines,
             QWidget *parent);

public slots:
  void slotDefault();

  unsigned int columns() const;
  unsigned int lines() const;

protected:
  QSpinBox*  m_columns;
  QSpinBox*  m_lines;
};

class KonsoleFind : public KEdFind
{
    Q_OBJECT
public:
  KonsoleFind( QWidget *parent = 0, const char *name=0, bool modal=true );
  bool reg_exp() const;

private slots:
  void slotEditRegExp();

private:
  QCheckBox*    m_asRegExp;
  QDialog*      m_editorDialog;
  QPushButton*  m_editRegExp;
};

#endif
