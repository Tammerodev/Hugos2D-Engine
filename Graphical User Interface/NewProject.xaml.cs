﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Graphical_User_Interface
{
    /// <summary>
    /// Interaction logic for NewProject.xaml
    /// </summary>
    
    public partial class NewProject : Window
    {
        
        public NewProject()
        {
            InitializeComponent();
        }

        private void createBtn_Click(object sender, RoutedEventArgs e)
        {
            Editor editor = new Editor();
            editor.Show();
            this.Close();
        }
    }
}