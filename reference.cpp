#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/engine.h>

using namespace std;

using EVP_CIPHER_CTX_ptr = unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

static const unsigned int KEY_SIZE = 32;
static const unsigned int BLOCK_SIZE = 16;

void gen_params(uint8_t key[KEY_SIZE], uint8_t iv[BLOCK_SIZE])
{
	int rc = RAND_bytes(key, KEY_SIZE);
	if (rc != 1) {
		throw runtime_error("RAND_bytes key failed");
	}

	rc = RAND_bytes(iv, BLOCK_SIZE);
	if (rc != 1) {
		throw runtime_error("RAND_bytes for iv failed");
	}
}

void encrypt(const uint8_t key[KEY_SIZE], const uint8_t iv[BLOCK_SIZE], const vector<uint8_t> &ptext, vector<uint8_t> &ctext)
{
        const EVP_CIPHER *type = EVP_get_cipherbynid(NID_gost89_cbc);
        if (type == nullptr) {
        	throw runtime_error("No encrypt ciphers");
	}

	EVP_CIPHER_CTX_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
	int rc = EVP_EncryptInit_ex(ctx.get(), type, NULL, key, iv);
	if (rc != 1) {
		throw runtime_error("EVP_EncryptInit_ex failed");
	}

	// Cipher text expands upto BLOCK_SIZE
	ctext.resize(ptext.size()+BLOCK_SIZE);
	int out_len1 = (int)ctext.size();

	rc = EVP_EncryptUpdate(ctx.get(), &ctext[0], &out_len1, &ptext[0], (int)ptext.size());
	if (rc != 1) {
		throw runtime_error("EVP_EncryptUpdate failed");
	}
	int out_len2 = (int)ctext.size() - out_len1;
	rc = EVP_EncryptFinal_ex(ctx.get(), &ctext[out_len1], &out_len2);
	if (rc != 1) {
		throw runtime_error("EVP_EncryptFinal_ex failed");
	}

	// Set cipher text size now that we know it
	ctext.resize(out_len1 + out_len2);
}

void decrypt(const uint8_t key[KEY_SIZE], const uint8_t iv[BLOCK_SIZE], const vector<uint8_t> &ctext, vector<uint8_t> &rtext)
{
        const EVP_CIPHER *type = EVP_get_cipherbynid(NID_gost89_cbc);
        if (type == nullptr) {
        	throw runtime_error("No decrypt ciphers");
	}

	EVP_CIPHER_CTX_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
	int rc = EVP_DecryptInit_ex(ctx.get(), type, NULL, key, iv);
	if (rc != 1) {
		throw runtime_error("EVP_DecryptInit_ex failed");
	}

	// Recovered text contracts upto BLOCK_SIZE
	rtext.resize(ctext.size());
	int out_len1 = (int)rtext.size();

	rc = EVP_DecryptUpdate(ctx.get(), &rtext[0], &out_len1, &ctext[0], (int)ctext.size());
	if (rc != 1) {
		throw runtime_error("EVP_DecryptUpdate failed");
	}

	int out_len2 = (int)rtext.size() - out_len1;
	rc = EVP_DecryptFinal_ex(ctx.get(), &rtext[out_len1], &out_len2);
	if (rc != 1) {
		throw runtime_error("EVP_DecryptFinal_ex failed");
	}

	// Set recovered text size now that we know it
	rtext.resize(out_len1 + out_len2);
}

int main(int, char **)
{
	OPENSSL_add_all_algorithms_conf();
	ERR_load_crypto_strings();

	ENGINE *eng = ENGINE_by_id("gost");
	if (eng == nullptr) {
		throw runtime_error("No engine");
	}
	ENGINE_init(eng);
	ENGINE_set_default(eng, ENGINE_METHOD_ALL);

	auto fn_c = ENGINE_get_ciphers(eng);
	if (fn_c == nullptr) {
		throw runtime_error("No ciphers");
	}
	const int *nids;
	const auto n = fn_c(eng, NULL, &nids, 0);
	for (int k = 0; k < n; ++k) {
		const EVP_CIPHER *type = EVP_get_cipherbynid(nids[k]);
		const char *name = EVP_CIPHER_name(type);
		cout << "Cipher: " << name << endl;
	}

	// plaintext, ciphertext, recovered text
	constexpr size_t datasize = 64 * 1024 * 1024;
	vector<uint8_t> ptext(datasize);
	vector<uint8_t> ctext(datasize);
	vector<uint8_t> rtext(datasize);

	uint8_t key[KEY_SIZE];
	uint8_t iv[BLOCK_SIZE];
	gen_params(key, iv);

	const auto start_time = chrono::high_resolution_clock::now();

	encrypt(key, iv, ptext, ctext);

	const auto middle_time = chrono::high_resolution_clock::now();

	decrypt(key, iv, ctext, rtext);

	const auto end_time = chrono::high_resolution_clock::now();
	const chrono::duration<double> encryption_time = middle_time - start_time;
	const chrono::duration<double> decryption_time = end_time - middle_time;

	cout << "Encryption: " << static_cast<size_t>(datasize * 8 / encryption_time.count() / (1024 * 1024)) << " Mbps" << endl;
	cout << "Decryption: " << static_cast<size_t>(datasize * 8 / decryption_time.count() / (1024 * 1024)) << " Mbps" << endl;

	return 0;
}
