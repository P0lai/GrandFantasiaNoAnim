#include <Windows.h>
#include <shellapi.h>

#pragma once

namespace NoAnim {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{

			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::LinkLabel^ linkLabel1;


	protected:

	protected:



	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();

			this->button1->AutoSize = true;
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(125)), static_cast<System::Int32>(static_cast<System::Byte>(161)),
				static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Consolas", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(210)), static_cast<System::Int32>(static_cast<System::Byte>(232)),
				static_cast<System::Int32>(static_cast<System::Byte>(133)));
			this->button1->Location = System::Drawing::Point(120, 131);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(190, 32);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Remove Animations";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);

			this->linkLabel1->ActiveLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(125)),
				static_cast<System::Int32>(static_cast<System::Byte>(161)), static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Font = (gcnew System::Drawing::Font(L"Arial", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linkLabel1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->linkLabel1->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->linkLabel1->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->linkLabel1->LinkVisited = true;
			this->linkLabel1->Location = System::Drawing::Point(12, 358);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(150, 22);
			this->linkLabel1->TabIndex = 2;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"Created by Polai";
			this->linkLabel1->VisitedLinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::linkLabel1_LinkClicked_1);

			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(23)), static_cast<System::Int32>(static_cast<System::Byte>(26)),
				static_cast<System::Int32>(static_cast<System::Byte>(33)));
			this->ClientSize = System::Drawing::Size(423, 389);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->button1);
			this->ForeColor = System::Drawing::Color::Transparent;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Grand Fantasia - NoAnim";
			this->TransparencyKey = System::Drawing::Color::Transparent;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		
	public:
		void changeValuesInMemory() 
		{
			int address = 0x42784E;
			bool count = false;

			HWND hGameWindow = FindWindow(NULL, L"Grand Fantasia");

			if (hGameWindow == NULL) 
			{
				MessageBox::Show("Grand Fantasia Is Not Open.");
			}
			else 
			{
				DWORD processID;
				GetWindowThreadProcessId(hGameWindow, &processID);

				HANDLE processHandle;
				processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

				int valueInMemory;
				ReadProcessMemory(processHandle, (LPVOID)address, &valueInMemory, 3, NULL);


				if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL) 
				{
					MessageBox::Show("Failed to open process. Try running as Administrator.");
				}
				else 
				{
					if (valueInMemory.ToString() == "6051545")
					{
						WriteProcessMemory(processHandle, (LPVOID)address, "\x90\x90\x90", 3, NULL);
						MessageBox::Show("Animations Removed.");
						button1->Text = "Return Animations";
					}
					else 
					{
						WriteProcessMemory(processHandle, (LPVOID)address, "\xD9\x56\x5C", 3, NULL);
						MessageBox::Show("Returned Animations.");
						button1->Text = "Remove Animations";
					}
					count = !count;
				}
			}
		}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		changeValuesInMemory();
	}
private: System::Void linkLabel1_LinkClicked_1(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) 
{
	System::Diagnostics::Process::Start("https://www.youtube.com/channel/UCuiqwmZfXrsAzAy0rRbixuQ");

}
};
}
