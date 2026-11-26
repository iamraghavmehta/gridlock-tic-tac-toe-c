document.addEventListener('DOMContentLoaded', () => {
  const boardEl = document.getElementById('board');
  const cells = document.querySelectorAll('.cell');
  const statusText = document.getElementById('statusText');
  const restartBtn = document.getElementById('restartBtn');
  const resetScoreBtn = document.getElementById('resetScoreBtn');
  const pvpModeBtn = document.getElementById('pvpModeBtn');
  const aiModeBtn = document.getElementById('aiModeBtn');
  const scoreXEl = document.getElementById('scoreX');
  const scoreOEl = document.getElementById('scoreO');
  const scoreDrawsEl = document.getElementById('scoreDraws');

  let board = ['', '', '', '', '', '', '', '', ''];
  let currentPlayer = 'X';
  let isGameActive = true;
  let isAiMode = false;
  let score = { X: 0, O: 0, draws: 0 };

  const WINNING_COMBOS = [
    [0, 1, 2], [3, 4, 5], [6, 7, 8], // Rows
    [0, 3, 6], [1, 4, 7], [2, 5, 8], // Columns
    [0, 4, 8], [2, 4, 6]             // Diagonals
  ];

  function checkWin(currentBoard, player) {
    for (let combo of WINNING_COMBOS) {
      if (combo.every(index => currentBoard[index] === player)) {
        return combo;
      }
    }
    return null;
  }

  function checkDraw(currentBoard) {
    return currentBoard.every(cell => cell !== '');
  }

  function handleCellClick(e) {
    const clickedCell = e.target;
    const index = parseInt(clickedCell.getAttribute('data-index'), 10);

    if (board[index] !== '' || !isGameActive) {
      return;
    }

    executeMove(index, currentPlayer);

    if (isGameActive && isAiMode && currentPlayer === 'O') {
      setTimeout(makeAiMove, 300);
    }
  }

  function executeMove(index, player) {
    board[index] = player;
    cells[index].textContent = player;
    cells[index].classList.add(player === 'X' ? 'x-mark' : 'o-mark');
    cells[index].setAttribute('disabled', 'true');

    const winningCombo = checkWin(board, player);
    if (winningCombo) {
      isGameActive = false;
      winningCombo.forEach(idx => cells[idx].classList.add('winning-cell'));
      statusText.textContent = `Player ${player} Wins!`;
      statusText.style.color = player === 'X' ? 'var(--color-x)' : 'var(--color-o)';
      score[player]++;
      updateScoreboardUI();
      return;
    }

    if (checkDraw(board)) {
      isGameActive = false;
      statusText.textContent = `Match Stalemate (Draw)`;
      statusText.style.color = 'var(--color-draw)';
      score.draws++;
      updateScoreboardUI();
      return;
    }

    currentPlayer = player === 'X' ? 'O' : 'X';
    statusText.textContent = `Player ${currentPlayer}'s Turn`;
    statusText.style.color = currentPlayer === 'X' ? 'var(--color-x)' : 'var(--color-o)';
  }

  function makeAiMove() {
    if (!isGameActive) return;

    // 1. Can AI win in this move?
    for (let i = 0; i < 9; i++) {
      if (board[i] === '') {
        board[i] = 'O';
        if (checkWin(board, 'O')) {
          board[i] = '';
          executeMove(i, 'O');
          return;
        }
        board[i] = '';
      }
    }

    // 2. Can Player X win in next move? Block them!
    for (let i = 0; i < 9; i++) {
      if (board[i] === '') {
        board[i] = 'X';
        if (checkWin(board, 'X')) {
          board[i] = '';
          executeMove(i, 'O');
          return;
        }
        board[i] = '';
      }
    }

    // 3. Take center if available
    if (board[4] === '') {
      executeMove(4, 'O');
      return;
    }

    // 4. Take random available corner/edge
    const available = [];
    board.forEach((val, idx) => { if (val === '') available.push(idx); });
    if (available.length > 0) {
      const randomIdx = available[Math.floor(Math.random() * available.length)];
      executeMove(randomIdx, 'O');
    }
  }

  function restartGame() {
    board = ['', '', '', '', '', '', '', '', ''];
    isGameActive = true;
    currentPlayer = 'X';
    statusText.textContent = `Player X's Turn`;
    statusText.style.color = 'var(--color-x)';

    cells.forEach(cell => {
      cell.textContent = '';
      cell.removeAttribute('disabled');
      cell.classList.remove('x-mark', 'o-mark', 'winning-cell');
    });
  }

  function updateScoreboardUI() {
    scoreXEl.textContent = score.X;
    scoreOEl.textContent = score.O;
    scoreDrawsEl.textContent = score.draws;
  }

  function resetScores() {
    score = { X: 0, O: 0, draws: 0 };
    updateScoreboardUI();
    restartGame();
  }

  // Event Listeners
  cells.forEach(cell => cell.addEventListener('click', handleCellClick));
  restartBtn.addEventListener('click', restartGame);
  resetScoreBtn.addEventListener('click', resetScores);

  pvpModeBtn.addEventListener('click', () => {
    isAiMode = false;
    pvpModeBtn.classList.add('active');
    aiModeBtn.classList.remove('active');
    restartGame();
  });

  aiModeBtn.addEventListener('click', () => {
    isAiMode = true;
    aiModeBtn.classList.add('active');
    pvpModeBtn.classList.remove('active');
    restartGame();
  });
});
