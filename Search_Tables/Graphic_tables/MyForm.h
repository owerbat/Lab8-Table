#pragma once
#include "../Search_Tables/Table.h"
#include "../Search_Tables/ArrayTable.h"
#include "../Search_Tables/HashTable.h"
#include "../Search_Tables/TreeTable.h"
#include <fstream>

namespace Graphic_tables {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		int count;
		char *buffer;
		TScanTable<string, int> *scantab;
		TSortTable<string, int> *sorttab;
		TArrayHash<string, int> *hashtab;
		TTreeTable<string, int> *treetab;
		TRecord<string, int> *maximum;
		TSortTable<int, string> *top;
		int *eff;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Number;
	public:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Key;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Value;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
			 


	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			count = 1000;
			buffer = new char[50];
			scantab = new TScanTable<string, int>(count);
			sorttab = new TSortTable<string, int>(count);
			hashtab = new TArrayHash<string, int>(count);
			treetab = new TTreeTable<string, int>();
			maximum = new TRecord<string, int>[10];
			top = new TSortTable<int, string>(count);
			eff = new int[4];

			ActivateTables();

			eff[0] = scantab->GetEfficiency();
			eff[1] = sorttab->GetEfficiency();
			eff[2] = hashtab->GetEfficiency();
			eff[3] = treetab->GetEfficiency();

			dataGridView1->RowCount = count;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	protected:


	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Number = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Key = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Value = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Number,
					this->Key, this->Value
			});
			this->dataGridView1->Location = System::Drawing::Point(31, 115);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(543, 428);
			this->dataGridView1->TabIndex = 0;
			// 
			// Number
			// 
			this->Number->HeaderText = L"¹";
			this->Number->Name = L"Number";
			// 
			// Key
			// 
			this->Key->HeaderText = L"Key";
			this->Key->Name = L"Key";
			this->Key->Width = 200;
			// 
			// Value
			// 
			this->Value->HeaderText = L"Value";
			this->Value->Name = L"Value";
			this->Value->Width = 200;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(31, 33);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(77, 32);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Scan";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(185, 33);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(77, 32);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Sort";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(344, 33);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(77, 32);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Hash";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(497, 33);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(77, 32);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Tree";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(727, 524);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(640, 524);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(68, 17);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Efficiency";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(939, 555);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: void ActivateTables() {
			ifstream ifs("..//Search_Tables//Machine_learning.txt");
			if (!ifs.is_open()) {
				throw exception("Reading file error");
			}

			while (!ifs.eof()) {
				ifs >> buffer;
				string str(buffer);
				TRecord<string, int> tmp(str, 1);

				if (scantab->Find(tmp.key)) {
					scantab->SetCurrValue(scantab->GetCurrent().value + 1);
				}
				else {
					if (!scantab->IsFull()) {
						scantab->Insert(tmp);
					}
					else {
						throw exception("Table size is too small!");
					}
				}

				if (sorttab->Find(tmp.key)) {
					sorttab->SetCurrValue(sorttab->GetCurrent().value + 1);
				}
				else {
					if (!sorttab->IsFull()) {
						sorttab->Insert(tmp);
					}
					else {
						throw exception("Table size is too small!");
					}
				}

				if (hashtab->Find(tmp.key)) {
					hashtab->SetCurrValue(hashtab->GetCurrent().value + 1);
				}
				else {
					if (!hashtab->IsFull()) {
						hashtab->Insert(tmp);
					}
					else {
						throw exception("Table size is too small!");
					}
				}

				if (treetab->Find(tmp.key)) {
					treetab->SetResValue(treetab->GetResRecord().value + 1);
				}
				else {
					if (!treetab->IsFull()) {
						treetab->Insert(tmp);
					}
					else {
						throw exception("Table size is too small!");
					}
				}
			}

			for (sorttab->Reset(); !sorttab->IsEnd(); sorttab->GoNext()) {
				top->Insert(TRecord<int, string>(sorttab->GetCurrent().value, sorttab->GetCurrent().key));
			}

			for (top->Reset(); !top->TenRecordsLeft(); top->GoNext());

			int i = 0;
			while (!top->IsEnd()) {
				maximum[i] = TRecord<string, int>(top->GetCurrent().value, top->GetCurrent().key);
				i++;
				top->GoNext();
			}

			ifs.close();
		}

	public: char *GetStr(string str) {
		int len = str.length();
		char *res = new char[len + 1];
		for (int i = 0; i < len; i++) {
			res[i] = str[i];
		}
		res[len] = '\0';
		return res;
	}

	public: String^ StrToStr(string str) {
		/*String^ res = gcnew String(GetStr(str));
		return res;*/
		return gcnew String(GetStr(str));
	}

	private: void ClearScreen() {
		for (int i = 0; i < count; i++) {
			dataGridView1->Rows[i]->Cells[0]->Value = i;
			dataGridView1->Rows[i]->Cells[1]->Value = "";
			dataGridView1->Rows[i]->Cells[2]->Value = "";
		}
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		TRecord<string, int> tmp;
		int i = 0;
		//dataGridView1->RowCount = count;
		ClearScreen();
		for (scantab->Reset(); !scantab->IsEnd(); scantab->GoNext()) {
			tmp = scantab->GetCurrent();
			//dataGridView1->Rows[i]->Cells[0]->Value = i;
			dataGridView1->Rows[i]->Cells[1]->Value = Convert::ToString(StrToStr(tmp.key));
			dataGridView1->Rows[i]->Cells[2]->Value = tmp.value;
			i++;
		}
		textBox1->Text = Convert::ToString(eff[0]);
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		TRecord<string, int> tmp;
		int i = 0;
		ClearScreen();
		for (sorttab->Reset(); !sorttab->IsEnd(); sorttab->GoNext()) {
			tmp = sorttab->GetCurrent();
			dataGridView1->Rows[i]->Cells[1]->Value = Convert::ToString(StrToStr(tmp.key));
			dataGridView1->Rows[i]->Cells[2]->Value = tmp.value;
			i++;
		}
		textBox1->Text = Convert::ToString(eff[1]);
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		TRecord<string, int> tmp;
		int i = 0;
		ClearScreen();
		for (hashtab->Reset(); !hashtab->IsEnd(); hashtab->GoNext()) {
			tmp = hashtab->GetCurrent();
			dataGridView1->Rows[i]->Cells[1]->Value = Convert::ToString(StrToStr(tmp.key));
			dataGridView1->Rows[i]->Cells[2]->Value = tmp.value;
			i++;
		}
		textBox1->Text = Convert::ToString(eff[2]);
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		TRecord<string, int> tmp;
		int i = 0;
		ClearScreen();
		for (treetab->Reset(); !treetab->IsEnd(); treetab->GoNext()) {
			tmp = treetab->GetCurrent();
			dataGridView1->Rows[i]->Cells[1]->Value = Convert::ToString(StrToStr(tmp.key));
			dataGridView1->Rows[i]->Cells[2]->Value = tmp.value;
			i++;
		}
		textBox1->Text = Convert::ToString(eff[3]);
	}
};
}
