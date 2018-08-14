#ifdef _GRAPHICS_
#include "interface.h"

Interface::Interface(QWidget *parent, Experiment *_exp, Viewer *_viewer )
    : QWidget(parent)
{
    m_experiment = _exp;                   // Experiment to run
    m_engine = new Engine(m_experiment);   // Engine use to run the simulation
    viewer = _viewer;

    //video = _video;
    frameRate = 12;

    flag_activate_loadGeno_buttons   = true;
    flag_activate_play_buttons       = false;
    flag_activate_step_buttons       = false;
    flag_activate_pause_buttons      = false;
    flag_activate_next_buttons       = false;
    flag_activate_quit_buttons       = true;
    flag_activate_rec_buttons        = true;
    flag_activate_stop_rec_buttons   = false;

    //   flag_activate_loadGeno_buttons       = false;
    //   flag_activate_reset_eval_loop_botton = true;
    //   flag_activate_play_buttons           = false;
    //   flag_activate_step_buttons           = false;
    //   flag_activate_pause_buttons          = false;
    //   flag_activate_next_buttons           = false;
    //   flag_activate_quit_buttons           = true;

    m_engine->setDelay( 50 );
    createButtons();
    //connect(m_engine, SIGNAL(advanced()), _viewer, SLOT(update()));
    //connect(m_engine, SIGNAL(advanced()), this, SLOT(changeWindowTitle()));

    mainLayout = new QVBoxLayout;
    //viewer->setMinimumHeight(300);

    //mainLayout->addWidget(_viewer, 1);
    mainLayout->addLayout(buttonsLayout, 0);
    setLayout(mainLayout);
    updateButtons();
    windowTitle = tr("Elio Tuci Sim-Artificial-World ");
    setWindowTitle(windowTitle);
    resize(800, 800); //resize the main widget
    move( 400, 100);//position the main widget

    //connect(exp, SIGNAL(currentEvaluation(int)), this, SLOT(changeWindowTitle(int)));
}

Interface::~Interface()
{
    delete m_engine;
}

void Interface::open()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Load a genotype"));
  if (!fileName.isEmpty()){
    ba = fileName.toLatin1();
    
    
    flag_activate_loadGeno_buttons       = false;
    //flag_activate_reset_eval_loop_botton = true;
    flag_activate_play_buttons           = true;
    flag_activate_step_buttons           = true;
    flag_activate_pause_buttons          = true;
    flag_activate_next_buttons           = true;
    flag_activate_quit_buttons           = true;
    
    // flag_activate_loadGeno_buttons       = false;
    // //flag_activate_reset_eval_loop_botton = true;
    // flag_activate_play_buttons           = false;
    // flag_activate_step_buttons           = false;
    // flag_activate_pause_buttons          = false;
    // flag_activate_next_buttons           = false;
    // flag_activate_quit_buttons           = true;
    
    updateButtons();
  }
}

void Interface::updateButtons()
{
    openButton->setEnabled            ( flag_activate_loadGeno_buttons );
    //reset_eval_loopButton->setEnabled ( flag_activate_reset_eval_loop_botton );
    playButton->setEnabled            ( flag_activate_play_buttons     );
    pauseButton->setEnabled           ( flag_activate_pause_buttons    );
    stopButton->setEnabled            ( flag_activate_next_buttons     );
    oneStepButton->setEnabled         ( flag_activate_step_buttons     );
    quitButton->setEnabled            ( flag_activate_quit_buttons     );
    recButton->setEnabled            ( flag_activate_rec_buttons     );
    stopRecButton->setEnabled            ( flag_activate_stop_rec_buttons     );
}

void Interface::createButtons()
{
    QSize iconSize(36, 36);

    openButton = new QToolButton;
    openButton->setIcon(QIcon("../IMAGES/open.png"));
    openButton->setIconSize(iconSize);
    openButton->setToolTip(tr("Load Genotype"));
    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

    //   reset_eval_loopButton = new QToolButton;
    //   reset_eval_loopButton->setIcon(QIcon("../IMAGES/reset.png"));
    //   reset_eval_loopButton->setIconSize(iconSize);
    //   reset_eval_loopButton->setToolTip(tr("Reset Evaluation Loop"));
    //   connect(reset_eval_loopButton, SIGNAL(clicked()), this, SLOT(active_reset_eval_loop()));


    playButton = new QToolButton;
    playButton->setIcon(QIcon("../IMAGES/play.png"));
    playButton->setIconSize(iconSize);
    playButton->setToolTip(tr("Run Sim"));
    connect(playButton, SIGNAL(clicked()), this, SLOT(active_play()));

    oneStepButton = new QToolButton;
    oneStepButton->setIcon(QIcon("../IMAGES/oneStep.png"));
    oneStepButton->setIconSize(iconSize);
    oneStepButton->setToolTip(tr("Step-by-Step"));
    connect(oneStepButton, SIGNAL(clicked()), this, SLOT(active_advance()));

    pauseButton = new QToolButton;
    //pauseButton->setCheckable(true);
    pauseButton->setIcon(QIcon("../IMAGES/pause.png"));
    pauseButton->setIconSize(iconSize);
    pauseButton->setToolTip(tr("Pause"));
    connect(pauseButton, SIGNAL(clicked(bool)), this, SLOT(active_pause()));

    stopButton = new QToolButton;
    stopButton->setIcon(QIcon("../IMAGES/stop.png"));
    stopButton->setIconSize(iconSize);
    stopButton->setToolTip(tr("Stop"));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(active_stop()));

    quitButton = new QToolButton;
    quitButton->setIcon(QIcon("../IMAGES/quit.png"));
    quitButton->setIconSize(iconSize);
    quitButton->setToolTip(tr("Quit"));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(active_quit()));

    recButton = new QToolButton;
    recButton->setIcon(QIcon("../IMAGES/rec.png"));
    recButton->setIconSize(iconSize);
    recButton->setToolTip(tr("Record"));
    connect(recButton, SIGNAL(clicked()), this, SLOT(active_rec()));

    stopRecButton = new QToolButton;
    stopRecButton->setIcon(QIcon("../IMAGES/stop.png"));
    stopRecButton->setIconSize(iconSize);
    stopRecButton->setToolTip(tr("Stop record"));
    connect(stopRecButton, SIGNAL(clicked()), this, SLOT(active_stop_rec()));

    QSpinBox *integerspinBox = new QSpinBox;
    integerspinBox->setRange (0, 50 );
    integerspinBox->setSingleStep(1);
    integerspinBox->setValue (0);
    connect(integerspinBox, SIGNAL(valueChanged(int)), this, SLOT(setGenotypeNumber(int )));

    QSpinBox *frameRateBox = new QSpinBox;
    frameRateBox->setRange (5, 50 );
    frameRateBox->setSingleStep(1);
    frameRateBox->setValue (frameRate);
    connect(frameRateBox, SIGNAL(valueChanged(int)), this, SLOT(setFrameRate(int)));

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(openButton);
    buttonsLayout->addWidget(integerspinBox);
    //buttonsLayout->addWidget(reset_eval_loopButton);
    buttonsLayout->addWidget(playButton);
    buttonsLayout->addWidget(oneStepButton);
    buttonsLayout->addWidget(pauseButton);
    buttonsLayout->addWidget(stopButton);
    buttonsLayout->addWidget(quitButton);
    buttonsLayout->addWidget(frameRateBox);
    buttonsLayout->addWidget(recButton);
    buttonsLayout->addWidget(stopRecButton);
    buttonsLayout->addStretch();
}

void  Interface::setGenotypeNumber(int id)
{
  int num_groups = 0;

    if( !ba.isEmpty() )
    {
      int num_groups = 0;
      vector < vector <chromosome_type> > genes;
      upload_genome_from_file <chromosome_type> ( ba.data(), genes, &num_groups );
      m_experiment->from_genome_to_controllers( genes, id );
    }
    else
    {
        cerr << " In Interface::setGenotypeNumber :: Genotype file name is missing " << endl;
        exit(EXIT_FAILURE);
    }

    //m_experiment->init_evaluations_loop( );
    //m_experiment->init_single_evaluation( );

    flag_activate_loadGeno_buttons       = false;
    //flag_activate_reset_eval_loop_botton = true;
    flag_activate_play_buttons           = true;
    flag_activate_step_buttons           = true;
    flag_activate_pause_buttons          = false;
    flag_activate_next_buttons           = false;
    flag_activate_quit_buttons           = true;
    updateButtons();
}

void  Interface::setFrameRate(int n)
{
    frameRate = n;
}

void Interface::active_play()
{
    flag_activate_loadGeno_buttons       = false;
    //flag_activate_reset_eval_loop_botton = false;
    flag_activate_play_buttons           = false;
    flag_activate_step_buttons           = false;
    flag_activate_pause_buttons          = true;
    flag_activate_next_buttons           = true;
    flag_activate_quit_buttons           = true;
    updateButtons();
    m_engine->play();
}

void Interface::active_advance()
{
    flag_activate_loadGeno_buttons       = false;
    //flag_activate_reset_eval_loop_botton = false;
    flag_activate_play_buttons           = true;
    flag_activate_step_buttons           = true;
    flag_activate_pause_buttons          = false;
    flag_activate_next_buttons           = true;
    flag_activate_quit_buttons           = true;
    updateButtons();
    m_engine->advance();
}

void Interface::active_pause()
{
    flag_activate_loadGeno_buttons       = false;
    //flag_activate_reset_eval_loop_botton = false;
    flag_activate_play_buttons           = true;
    flag_activate_step_buttons           = true;
    flag_activate_pause_buttons          = false;
    flag_activate_next_buttons           = true;
    flag_activate_quit_buttons           = true;
    updateButtons();
    m_engine->pause();
}

void Interface::active_stop()
{
    flag_activate_loadGeno_buttons       = true;
    //flag_activate_reset_eval_loop_botton = true;
    flag_activate_play_buttons           = true;
    flag_activate_step_buttons           = true;
    flag_activate_pause_buttons          = false;
    flag_activate_next_buttons           = false;
    flag_activate_quit_buttons           = true;
    updateButtons();
    m_engine->stop();
}

void Interface::active_quit()
{
  if(viewer->isRecording())
    //video->StopRec();
    viewer->video_close( );
  exit(EXIT_SUCCESS);
  //exit(0);
  /*
    if(video->isRecording())
    video->StopRec();
  */
}

void Interface::active_rec()
{ 
  flag_activate_rec_buttons = false;
  flag_activate_stop_rec_buttons = true;
  updateButtons();
  viewer->set_recording(true);
  viewer->video_open( ); // CODEC_ID_MPEG4 not supported by my VLC yet!

  // viewer->set_recording(true);
  // viewer->video_open( ); // CODEC_ID_MPEG4 not supported by my VLC yet!
  
  // //video->StartRec((int)viewer->width(), (int)viewer->height(), (float)frameRate);
}

void Interface::active_stop_rec()
{
    flag_activate_rec_buttons = true;
    flag_activate_stop_rec_buttons = false;
    updateButtons();
    viewer->video_close( );
    //video->StopRec();
}

void Interface::changeWindowTitle()
{
    setWindowTitle(windowTitle + " - Evaluation : " + QString::number(m_experiment->getEvaluationCounter()+1));
}

// void Interface::active_reset_eval_loop(){
//   flag_activate_loadGeno_buttons       = true;
//   flag_activate_reset_eval_loop_botton = false;
//   flag_activate_play_buttons           = true;
//   flag_activate_step_buttons           = true;
//   flag_activate_pause_buttons          = false;
//   flag_activate_next_buttons           = false;
//   flag_activate_quit_buttons           = true;
//   updateButtons();
//   m_experiement->init_evaluations_loop( );
// }
#endif
