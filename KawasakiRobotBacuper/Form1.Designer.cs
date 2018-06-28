namespace KawasakiRobotBacuper
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
            this.trigUSB = new System.Windows.Forms.Button();
            this.textRobotName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.trigRS232 = new System.Windows.Forms.Button();
            this.labStatus = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnSide = new System.Windows.Forms.Button();
            this.textcConsole = new KawasakiRobotBacuper.Console();
            this.SuspendLayout();
            // 
            // boxPortList
            // 
            this.boxPortList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.boxPortList.Font = new System.Drawing.Font("Microsoft Tai Le", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.boxPortList.FormattingEnabled = true;
            this.boxPortList.Location = new System.Drawing.Point(351, 12);
            this.boxPortList.Name = "boxPortList";
            this.boxPortList.Size = new System.Drawing.Size(571, 44);
            this.boxPortList.Sorted = true;
            this.boxPortList.TabIndex = 0;
            this.boxPortList.SelectedIndexChanged += new System.EventHandler(this.boxPortList_SelectedIndexChanged);
            // 
            // trigUSB
            // 
            this.trigUSB.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.trigUSB.Location = new System.Drawing.Point(19, 155);
            this.trigUSB.Name = "trigUSB";
            this.trigUSB.Size = new System.Drawing.Size(140, 140);
            this.trigUSB.TabIndex = 3;
            this.trigUSB.Text = "USB";
            this.trigUSB.UseVisualStyleBackColor = true;
            this.trigUSB.Click += new System.EventHandler(this.trigUSB_Click);
            // 
            // textRobotName
            // 
            this.textRobotName.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textRobotName.Location = new System.Drawing.Point(19, 105);
            this.textRobotName.Name = "textRobotName";
            this.textRobotName.Size = new System.Drawing.Size(300, 44);
            this.textRobotName.TabIndex = 4;
            this.textRobotName.Text = "Backup";
            this.textRobotName.TextChanged += new System.EventHandler(this.textRobotName_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(117, 37);
            this.label1.TabIndex = 6;
            this.label1.Text = "Status:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // trigRS232
            // 
            this.trigRS232.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.trigRS232.Location = new System.Drawing.Point(179, 155);
            this.trigRS232.Name = "trigRS232";
            this.trigRS232.Size = new System.Drawing.Size(140, 140);
            this.trigRS232.TabIndex = 2;
            this.trigRS232.Text = "RS232";
            this.trigRS232.UseVisualStyleBackColor = true;
            this.trigRS232.Click += new System.EventHandler(this.trigRS232_Click);
            // 
            // labStatus
            // 
            this.labStatus.AutoSize = true;
            this.labStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labStatus.ForeColor = System.Drawing.Color.Blue;
            this.labStatus.Location = new System.Drawing.Point(140, 9);
            this.labStatus.Name = "labStatus";
            this.labStatus.Size = new System.Drawing.Size(179, 37);
            this.labStatus.TabIndex = 7;
            this.labStatus.Text = "Connecting";
            this.labStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(12, 65);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(200, 37);
            this.label2.TabIndex = 8;
            this.label2.Text = "Robot name:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btnSide
            // 
            this.btnSide.Font = new System.Drawing.Font("Microsoft Sans Serif", 25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.btnSide.Location = new System.Drawing.Point(244, 428);
            this.btnSide.Name = "btnSide";
            this.btnSide.Size = new System.Drawing.Size(75, 75);
            this.btnSide.TabIndex = 9;
            this.btnSide.Text = ">";
            this.btnSide.UseVisualStyleBackColor = true;
            this.btnSide.Click += new System.EventHandler(this.btnSide_Click);
            // 
            // textcConsole
            // 
            this.textcConsole.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textcConsole.Location = new System.Drawing.Point(351, 71);
            this.textcConsole.Name = "textcConsole";
            this.textcConsole.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.ForcedVertical;
            this.textcConsole.Size = new System.Drawing.Size(571, 432);
            this.textcConsole.TabIndex = 5;
            this.textcConsole.Text = "";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(873, 515);
            this.Controls.Add(this.btnSide);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.labStatus);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textcConsole);
            this.Controls.Add(this.trigUSB);
            this.Controls.Add(this.textRobotName);
            this.Controls.Add(this.trigRS232);
            this.Controls.Add(this.boxPortList);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "Kawasaki Robot Backuper";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox boxPortList;
        private System.Windows.Forms.Button trigUSB;
        private System.Windows.Forms.TextBox textRobotName;
        private Console textcConsole;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button trigRS232;
        private System.Windows.Forms.Label labStatus;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnSide;
    }
}

