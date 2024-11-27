# Makefile for Genetic Program Project (Windows / MinGW)

# Derleyici ve bayraklar
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -g -Wall
LDFLAGS = -Llib
TARGET = bin/main.exe

# Kaynak dosyalar ve nesne dosyaları
SRC = src/main.cpp src/Kromozom.cpp src/Populasyon.cpp
OBJ = $(SRC:src/%.cpp=lib/%.o)

# Varsayılan hedef: Programı derle ve çalıştırılabilir dosya oluştur
all: $(TARGET)

# Çalıştırılabilir dosyayı oluştur
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# .cpp dosyalarını .o dosyalarına dönüştür
lib/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Temizleme işlemi: Nesne dosyalarını ve yürütülebilir dosyayı siler
clean:
	del /Q lib\*.o bin\main.exe

# Programı çalıştır
run: $(TARGET)
	$(TARGET)
