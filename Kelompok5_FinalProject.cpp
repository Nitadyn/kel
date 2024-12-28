#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Struktur untuk menu item
struct MenuItem {
    string name;
    double price;
    int salesCount;

    MenuItem(string n = "", double p = 0.0) : name(n), price(p), salesCount(0) {}
};

// Struktur untuk menyimpan data cuaca dan penjualan
struct WeatherSalesData {
    string date;
    string weatherCondition;
    double totalSales;
    int menuItemsSold[3]; // Array untuk menyimpan jumlah terjual per menu
};

// Enumerasi untuk role pengguna
enum UserRole {
    OWNER,
    STAFF
};

// Kelas untuk mengelola sistem bisnis yang adaptif terhadap cuaca
class WeatherAdaptiveFoodBusiness {
private:
    vector<WeatherSalesData> weatherSalesRecords;
    UserRole currentRole;
    MenuItem menuItems[3];
    string bestSeller;
    string rainyDaySpecialMenu;

    // Fungsi untuk membersihkan buffer input
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Inisialisasi menu
    void initializeMenu() {
        menuItems[0] = MenuItem("Mie Ayam Biasa", 15000);
        menuItems[1] = MenuItem("Mie Ayam Pangsit", 20000);
        menuItems[2] = MenuItem("Mie Ayam Bakso", 25000);
        bestSeller = "Mie Ayam Biasa"; // Set best seller awal
    }

    // Inisialisasi data penjualan contoh
    void initializeSampleData() {
        struct SampleData {
            string date;
            string weather;
            int biasa;
            int pangsit;
            int bakso;
        };

        SampleData samples[] = {
            {"01-12-2024", "Cerah", 25, 20, 15},
            {"02-12-2024", "Berawan", 18, 22, 17},
            {"03-12-2024", "Hujan", 10, 12, 20},
            {"04-12-2024", "Cerah", 30, 25, 10},
            {"05-12-2024", "Berawan", 20, 25, 18},
            {"06-12-2024", "Hujan", 12, 15, 22}
        };

        for (const auto& sample : samples) {
            WeatherSalesData salesData = {};
            salesData.date = sample.date;
            salesData.weatherCondition = sample.weather;
            salesData.menuItemsSold[0] = sample.biasa;
            salesData.menuItemsSold[1] = sample.pangsit;
            salesData.menuItemsSold[2] = sample.bakso;

            salesData.totalSales = sample.biasa * menuItems[0].price +
                sample.pangsit * menuItems[1].price +
                sample.bakso * menuItems[2].price;

            weatherSalesRecords.push_back(salesData);

            // Update total sales count per menu
            menuItems[0].salesCount += sample.biasa;
            menuItems[1].salesCount += sample.pangsit;
            menuItems[2].salesCount += sample.bakso;
        }

        // Update best seller
        int maxSales = 0;
        for (int i = 0; i < 3; i++) {
            if (menuItems[i].salesCount > maxSales) {
                maxSales = menuItems[i].salesCount;
                bestSeller = menuItems[i].name;
            }
        }
    }

public:
    WeatherAdaptiveFoodBusiness() : currentRole(STAFF) {
        initializeMenu();
        initializeSampleData();
    }

    void setRole(UserRole role) {
        currentRole = role;
    }

    // Fungsi untuk input kondisi cuaca harian (Owner)
    void inputDailyWeatherCondition() {
        if (currentRole != OWNER) {
            cout << "Fitur ini hanya tersedia untuk owner." << endl;
            return;
        }

        cout << "\n--- Input Kondisi Cuaca Harian ---" << endl;

        WeatherSalesData salesData = {};
        cout << "Masukkan tanggal (YYYY-MM-DD): ";
        cin >> salesData.date;

        cout << "Masukkan kondisi cuaca (Cerah/Hujan/Berawan): ";
        cin >> salesData.weatherCondition;

        cout << "Masukkan jumlah penjualan per menu:" << endl;
        salesData.totalSales = 0;

        for (int i = 0; i < 3; i++) {
            cout << menuItems[i].name << " (terjual): ";
            cin >> salesData.menuItemsSold[i];
            salesData.totalSales += salesData.menuItemsSold[i] * menuItems[i].price;
        }

        weatherSalesRecords.push_back(salesData);
        cout << "Data cuaca dan penjualan berhasil ditambahkan!" << endl;
    }

    // Fungsi untuk melihat catatan penjualan per cuaca (Owner)
    void displaySalesRecordsByWeather() {
        if (currentRole != OWNER) {
            cout << "Fitur ini hanya tersedia untuk owner." << endl;
            return;
        }

        if (weatherSalesRecords.empty()) {
            cout << "Belum ada data penjualan." << endl;
            return;
        }

        cout << "\n--- Catatan Penjualan per Cuaca ---" << endl;
        cout << left << setw(12) << "Tanggal"
            << setw(15) << "Cuaca"
            << setw(12) << "Total (Rp)" << endl;
        cout << string(50, '-') << endl;

        for (const auto& salesData : weatherSalesRecords) {
            cout << left << setw(12) << salesData.date
                << setw(15) << salesData.weatherCondition
                << setw(12) << fixed << setprecision(2) << salesData.totalSales << endl;
        }
    }

    // Fungsi untuk set menu spesial cuaca hujan (Owner)
    void setRainyDaySpecialMenu() {
        if (currentRole != OWNER) {
            cout << "Fitur ini hanya tersedia untuk owner." << endl;
            return;
        }

        cout << "\n--- Set Menu Spesial Cuaca Hujan ---" << endl;
        cout << "Masukkan menu spesial untuk hari hujan: ";
        clearInputBuffer();
        getline(cin, rainyDaySpecialMenu);
        cout << "Menu spesial untuk cuaca hujan berhasil disimpan!" << endl;
    }

    // Fungsi untuk menampilkan menu spesial cuaca hujan (Staff)
    void displayRainyDaySpecialMenu() {
        if (currentRole != STAFF) {
            cout << "Fitur ini hanya tersedia untuk staff." << endl;
            return;
        }

        if (rainyDaySpecialMenu.empty()) {
            cout << "Belum ada menu spesial untuk cuaca hujan." << endl;
        }
        else {
            cout << "\n--- Menu Spesial Cuaca Hujan ---" << endl;
            cout << "Menu: " << rainyDaySpecialMenu << endl;
        }
    }

    // Fungsi untuk menghitung total pendapatan harian (Staff)
    void calculateDailyRevenue() {
        if (currentRole != STAFF) {
            cout << "Fitur ini hanya tersedia untuk staff." << endl;
            return;
        }

        double totalRevenue = 0.0;

        cout << "\n--- Total Pendapatan Harian ---" << endl;
        for (int i = 0; i < 3; i++) {
            double revenue = menuItems[i].salesCount * menuItems[i].price;
            totalRevenue += revenue;

            cout << menuItems[i].name << ": "
                << menuItems[i].salesCount << " porsi, Pendapatan: Rp "
                << fixed << setprecision(2) << revenue << endl;
        }

        cout << "Total Pendapatan: Rp " << fixed << setprecision(2) << totalRevenue << endl;
    }
};

// Fungsi untuk memilih role
UserRole selectRole() {
    int roleChoice;
    cout << "\n=== Pilih Role ===" << endl;
    cout << "1. Owner" << endl;
    cout << "2. Staff" << endl;
    cout << "Pilih role (1-2): ";
    cin >> roleChoice;

    return (roleChoice == 1) ? OWNER : STAFF;
}

// Fungsi untuk menampilkan menu sistem
void displaySystemMenu(UserRole role) {
    cout << "\n=== Weather-Adaptive Food Business System ===" << endl;
    if (role == OWNER) {
        cout << "1. Input Kondisi Cuaca Harian" << endl;
        cout << "2. Lihat Catatan Penjualan per Cuaca" << endl;
        cout << "3. Set Menu Spesial Cuaca Hujan" << endl;
        cout << "4. Keluar" << endl;
    }
    else {
        cout << "1. Lihat Menu Spesial Cuaca Hujan" << endl;
        cout << "2. Hitung Total Pendapatan Harian" << endl;
        cout << "3. Keluar" << endl;
    }
    cout << "Pilih opsi: ";
}

int main() {
    WeatherAdaptiveFoodBusiness business;
    UserRole currentRole = selectRole();
    business.setRole(currentRole);
    int choice;

    do {
        displaySystemMenu(currentRole);
        cin >> choice;

        if (currentRole == OWNER) {
            switch (choice) {
            case 1:
                business.inputDailyWeatherCondition();
                break;
            case 2:
                business.displaySalesRecordsByWeather();
                break;
            case 3:
                business.setRainyDaySpecialMenu();
                break;
            case 4:
                cout << "Terima kasih! Sampai jumpa." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
            }
        }
        else { // STAFF
            switch (choice) {
            case 1:
                business.displayRainyDaySpecialMenu();
                break;
            case 2:
                business.calculateDailyRevenue();
                break;
            case 3:
                cout << "Terima kasih! Sampai jumpa." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
            }
        }
    } while ((currentRole == OWNER && choice != 4) || (currentRole == STAFF && choice != 3));

    return 0;
}
