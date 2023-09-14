#!/bin/bash

# Убедитесь, что файл numbers.txt не существует, чтобы избежать перезаписи
if [ -e numbers.txt ]; then
  echo "Файл numbers.txt уже существует. Удалите его, если хотите создать новый."
  exit 1
fi

# Генерируем 150 случайных чисел и записываем их в файл numbers.txt
for ((i=1; i<=150; i++)); do
  random_number=$(od -An -N2 -i /dev/random | awk '{print $1}')
  echo "$random_number" >> numbers.txt
done

echo "Файл numbers.txt успешно создан с 150 случайными числами."