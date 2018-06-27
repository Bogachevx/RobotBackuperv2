namespace RobotBackuperv2
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.boxPortList = new System.Windows.Forms.ComboBox();
            this.textConsole = new System.Windows.Forms.TextBox();
            this.trigRS232 = new System.Windows.Forms.Button();
            this.trigUSB = new System.Windows.Forms.Button();
            this.textRobotName = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // boxPortList
            // 
            this.boxPortList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.boxPortList.FormattingEnabled = true;
            this.boxPortList.Location = new System.Drawing.Point(12, 12);
            this.boxPortList.Name = "boxPortList";
            this.boxPortList.Size = new System.Drawing.Size(121, 21);
            this.boxPortList.TabIndex = 0;
            this.boxPortList.SelectedIndexChanged += new System.EventHandler(this.boxPortList_SelectedIndexChanged);
            // 
            // textConsole
            // 
            this.textConsole.Location = new System.Drawing.Point(140, 12);
            this.textConsole.Multiline = true;
            this.textConsole.Name = "textConsole";
            this.textConsole.Size = new System.Drawing.Size(496, 275);
            this.textConsole.TabIndex = 1;
            // 
            // trigRS232
            // 
            this.trigRS232.Location = new System.Drawing.Point(26, 118);
            this.trigRS232.Name = "trigRS232";
            this.trigRS232.Size = new System.Drawing.Size(65, 40);
            this.trigRS232.TabIndex = 2;
            this.trigRS232.Text = "RS232";
            this.trigRS232.UseVisualStyleBackColor = true;
            // 
            // trigUSB
            // 
            this.trigUSB.Location = new System.Drawing.Point(26, 164);
            this.trigUSB.Name = "trigUSB";
            this.trigUSB.Size = new System.Drawing.Size(65, 40);
            this.trigUSB.TabIndex = 3;
            this.trigUSB.Text = "USB";
            this.trigUSB.UseVisualStyleBackColor = true;
            this.trigUSB.Click += new System.EventHandler(this.trigUSB_Click);
            // 
            // textRobotName
            // 
            this.textRobotName.Location = new System.Drawing.Point(12, 62);
            this.textRobotName.Name = "textRobotName";
            this.textRobotName.Size = new System.Drawing.Size(121, 20);
            this.textRobotName.TabIndex = 4;
            this.textRobotName.Text = "Backup";
            this.textRobotName.TextChanged += new System.EventHandler(this.textRobotName_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.textRobotName);
            this.Controls.Add(this.trigUSB);
            this.Controls.Add(this.trigRS232);
            this.Controls.Add(this.textConsole);
            this.Controls.Add(this.boxPortList);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox boxPortList;
        private System.Windows.Forms.TextBox textConsole;
        private System.Windows.Forms.Button trigRS232;
        private System.Windows.Forms.Button trigUSB;
        private System.Windows.Forms.TextBox textRobotName;
    }
}

